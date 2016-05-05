#define PI 3.14159265358979323846264338327950288

#include <cstdio>
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::vec3 position(4,3,3);

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

glm::vec3 getPosition() {
	return position;
}

float mabs(float x) {
	return x > 0 ? x : -x;
}

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
double t = 0;
double x_mouse_stored = 0.0, y_mouse_stored = 0.0;
double horizontalAngle = 0, verticalAngle = 0;
int prevState = GLFW_RELEASE;

void computeMatricesFromInputs() {
  int rightClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  if (prevState == GLFW_RELEASE && rightClick == GLFW_PRESS) {

  }

	if (rightClick == GLFW_PRESS) {
		horizontalAngle += mouseSpeed * float(x_mouse_stored - xpos);
		verticalAngle   += mouseSpeed * float(y_mouse_stored - ypos);

	}
	x_mouse_stored = xpos;
	y_mouse_stored = ypos;

  // t += 0.005f;
  // position.x = 3 * cos(t);
  // position.y = 0;
  // position.z = 3 * sin(t);
  position.x = 3*cos(-verticalAngle) * sin(horizontalAngle);
	position.y = 3*sin(-verticalAngle);
	position.z = 3*cos(-verticalAngle) * cos(horizontalAngle);
	//printf("%f\t%f\t%f\n", position.x, position.y, position.z);
	//printf("%f\t%f\t%d\n",horizontalAngle, verticalAngle, mabs(verticalAngle)>PI / 2.0?-1:1);

  ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  ViewMatrix = glm::lookAt(
			position,           // Camera is here
      glm::vec3(0,0,0),
      glm::vec3(0,mabs(verticalAngle)>PI / 2.0?-1:1,0) //ask about it
	);
	prevState = rightClick;
}
