#include "player.hpp"

Player::Player(const unsigned int p_vaoId, const unsigned int p_vertexCount)
	: Model(p_vaoId, p_vertexCount)
{

	m_run_speed = 100;
	m_turn_speed = 120;
	m_current_speed = 0;
	m_current_turn_speed = 0;
	m_upwards_speed = 0;
	m_jump_power = 50;
	m_gravity = -100;
	m_in_air = false;
	terrain_height = 0;
}

void Player::checkInputs(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_current_speed = m_run_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_current_speed = -m_run_speed;
	}
	else
	{
		m_current_speed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_current_turn_speed = -m_turn_speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_current_turn_speed = m_turn_speed;
	}
	else
	{
		m_current_turn_speed = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

		jump();
	}
}
void Player::move(GLFWwindow *p_window, GLfloat p_delta_time, std::vector <Model> modelos)
{

	checkInputs(p_window);
	increaseRotation(0, m_current_turn_speed * p_delta_time, 0);
	GLfloat distanceZ = m_current_speed * p_delta_time;
	GLfloat distanceX = m_current_turn_speed * p_delta_time;
	GLfloat dx = (GLfloat)(distanceZ * glm::sin(glm::radians(getRotation().y)));
	GLfloat dz = (GLfloat)(distanceZ * glm::cos(glm::radians(getRotation().y)));

	increasePosition(dx, 0, dz, modelos);
	m_upwards_speed += m_gravity * p_delta_time;
	increasePosition(0, m_upwards_speed * p_delta_time, 0, modelos);

	if (getPosition().y < terrain_height)
	{

		m_upwards_speed = 0;
		setPosition(glm::vec3(getPosition().x, terrain_height, getPosition().z));
		m_in_air = false;
	}
}

void Player::jump()
{

	if (!m_in_air)
	{

		m_upwards_speed = m_jump_power;
		m_in_air = true;
	}
}

Player::~Player()
{
}
