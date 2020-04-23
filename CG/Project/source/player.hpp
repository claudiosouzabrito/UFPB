#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "model.hpp"
#include <GLFW/glfw3.h>

class Player : public Model
{

private:
	GLfloat m_run_speed;
	GLfloat m_turn_speed;
	GLfloat m_current_speed;
	GLfloat m_current_turn_speed;
	GLfloat m_gravity;
	GLfloat m_jump_power;
	GLfloat m_upwards_speed;
	bool m_in_air;

public:
	GLfloat terrain_height;
	Player(const unsigned int p_vaoId, const unsigned int p_vertexCount);
	void move(GLFWwindow *p_window, GLfloat p_delta_time, std::vector <Model> modelos);
	void checkInputs(GLFWwindow *window);
	void jump();
	~Player();
};

#endif
