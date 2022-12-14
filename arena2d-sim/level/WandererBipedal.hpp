#ifndef WANDERERBIPEDAL_H
#define WANDERERBIPEDAL_H

#include "Wanderer.hpp"
#include <arena/PhysicsWorld.hpp>
#include <engine/zVector2d.hpp>
#include <engine/GlobalSettings.hpp>
#include <ctime>

#define HUMAN_LEG_SIZE 0.09f
#define HUMAN_LEG_DISTANCE 0.04f

/* human wanderer represented by two circles (legs)
 */
class WandererBipedal : public Wanderer{
    public:
	/* constructor */
    WandererBipedal(b2World * w, const b2Vec2 & position, float velocity, unsigned int type, unsigned int mode=0,
	                std::vector<b2Vec2> waypoints={}, int stop_counter_threshold=1, 
                    float change_rate=1.0f, float stop_rate=0.1f, float max_angle_velo = 60.0f);

	/* return radius of circle surrounding all fixtures
	 */
	static float getRadius(){return (HUMAN_LEG_DISTANCE+2*HUMAN_LEG_SIZE)/2.f;}

    /* updates velocity accoriding to change/stop rate
     */

    void update(bool chat_flag) override;

protected:
    /* update velocity
     * this function is called in update() if a randomly sampled value [0, 1] is less than the change rate
     */
    //void updateVelocity() override;

    void updateVelocityRandomMode() override;

	void updateVelocityPathMode() override;

    float _counter;

    // Legposture parameter
    double step_frequency_factor;
    double step_width_factor;

    //chatting time parameter;

    int chat_threshold;
    int chat_counter;

    //preventing eternal stuck in chat
    int chat_reset_threshold;
    int chat_reset_counter;

};

#endif
