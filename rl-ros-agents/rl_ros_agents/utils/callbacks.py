from stable_baselines3.common.callbacks import BaseCallback
import numpy as np
import os
from stable_baselines3.common.results_plotter import load_results, ts2xy
from typing import Union


import rospy


class SaveOnBestTrainingRewardCallback(BaseCallback):
    """
    Callback for saving a model (the check is done every ``check_freq`` steps)
    based on the training reward (in practice, we recommend using ``EvalCallback``).

    :param check_freq: (int)
    :param log_dir: (str) Path to the folder where the model will be saved.
      It must contains the file created by the ``Monitor`` wrapper.
    :param verbose: (int)
    :param reward_bound: (int) upper_limit of the reward that the agent should achieve

    """

    def __init__(self, 
                check_freq: int, 
                log_dir: str, 
                verbose=1, 
                reward_bound: Union[int, None] = None):
                
        super(SaveOnBestTrainingRewardCallback, self).__init__(verbose)
        self.check_freq = check_freq
        self.log_dir = log_dir
        self.save_path = os.path.join(log_dir, 'best_model')
        self.best_mean_reward = -np.inf
        self.reward_bound = reward_bound

        self.stage = rospy.get_param("stage/stage")        
        self.cur_stage = 1
        self.arrived_max_stage = 1

    def _init_callback(self) -> None:
        # Create folder if needed
        if self.save_path is not None:
            os.makedirs(self.save_path, exist_ok=True)

    def _on_step(self) -> bool:
        rospy.logdebug("on_step callback")
        if self.n_calls % self.check_freq == 0:
            # Retrieve training reward
            x, y = ts2xy(load_results(self.log_dir), 'timesteps')
            if len(x) > 0:
                # Mean training reward over the last 100 episodes
                mean_reward = np.mean(y[-100:])
                if self.verbose > 0:
                    if self.stage:
                        self.cur_stage = rospy.get_param("stage/curstage")
                        self.arrived_max_stage = rospy.get_param("stage/maxstage")
                        print("\nCurrent stage is: {}, arrived maximal stage is: {}".format(self.cur_stage, self.arrived_max_stage))
                    print("Num timesteps: {}".format(self.num_timesteps))
                    print(
                        "Best mean reward: {:.2f} - Last mean reward per episode: {:.2f}".format(self.best_mean_reward, mean_reward))
                    print(f"self.reward_bound is {self.reward_bound} and mean_ward is {mean_reward}")

                # New best model, you could save the agent here
                if mean_reward > self.best_mean_reward:
                    self.best_mean_reward = mean_reward
                    # Example for saving best model
                    if self.verbose > 0:
                        print("Saving new best model to {}".format(self.save_path))
                    self.model.save(self.save_path)
                # early stop the training
                if self.reward_bound is not None and mean_reward > self.reward_bound:
                    print("early stop!")
                    return False

        return True
