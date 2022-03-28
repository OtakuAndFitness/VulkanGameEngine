#include "lve_model.hpp"

namespace lve {
	LveModel::LveModel(LveDevice& device, const std::vector<Vertex>& vertices) : lveDevice{device} {
		createVertexBuffers(vertices);
	}

	LveModel::~LveModel() {
		vkDestroyBuffer(lveDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(lveDevice.device(), vertexBufferMemory, nullptr);
	}

	void LveModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		lveDevice.createBuffer(
			bufferSize, 
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 
			vertexBuffer, 
			vertexBufferMemory);

		void* data;
		vkMapMemory(lveDevice.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(lveDevice.device(), vertexBufferMemory);
	}

	void LveModel::Draw(VkCommandBuffer commandBufrer) {
		vkCmdDraw(commandBufrer, vertexCount, 1, 0, 0);
	}

	void LveModel::Bind(VkCommandBuffer commandBufrer) {
		VkBuffer buffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBufrer, 0, 1, buffers, offsets);
	}

	std::vector<VkVertexInputBindingDescription> LveModel::Vertex::getBindingDescriptions() {
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescriptions;
		//return { {0,sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX} };

	}

	std::vector<VkVertexInputAttributeDescription> LveModel::Vertex::getAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);
		return attributeDescriptions;
	}

}