#pragma once

#include <vulkan\vulkan.h>
#include <array>
#include "Vector2.h"
#include "Sprite.h"
#include "SpriteSheet.h"
//#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;
		glm::vec2 texCoord;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

			return attributeDescriptions;
		}
	};

	public:
		//	Variables
		SpriteSheet sprite;		//	Sprite of the object
		std::vector<Vertex> vertices;
		double radius;			//	Radius of the object
		double bound;			//	Radius of the bounding circle; used for collision detection
		Vector2 pos;			//	Vector representing the position of the object
		Vector2 vel;			//	Vector representing the velocity of the object
		double m;				//	Mass of the object
		Vector2 force;
		Vector2 force_old;
		Vector2 pos_old;
		Vector2 vel_old;

		//	Constructors
		GameObject();
		GameObject(double r);
		GameObject(double r, double bs);
		GameObject(double r, double bs, Vector2 position, Vector2 velocity);
		GameObject(double r, Vector2 position, Vector2 velocity);
		GameObject(SpriteSheet ss, double r, Vector2 position, Vector2 velocity);

		//	Functions
		void setVertices();
		std::vector<Vertex> getVertices();
		void setMass(double mass);
		void setSprite(SpriteSheet ss);
		std::string toString();
};