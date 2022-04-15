#pragma once

#include "lve_device.hpp"   
#include <vector>
#include <string>

namespace lve {
	
	struct PipelineConfigInfo {
		//PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator = (const PipelineConfigInfo &) = delete;
		//VkViewport viewport;
		//VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;

	};

	class LvePipeline {
		public:
			LvePipeline(
				const std::string& vertFilepath, 
				const std::string& fragFilePath, 
				LveDevice &device, 
				const PipelineConfigInfo &configInfo 
			);

			~LvePipeline();

			LvePipeline(const LvePipeline&) = delete;
			LvePipeline& operator=(const LvePipeline&) = delete;

			void	Bind(VkCommandBuffer commandBuffer);

			static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

		private:
			static std::vector<char> readFile(const std::string& filepath);

			void createGraphicsPipeline(
				const std::string& vertFilepath, 
				const std::string& fragFilePath,
				const PipelineConfigInfo& configInfo
			);

			void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

			LveDevice& lveDevice;
			VkPipeline graphicsPipeline;
			VkShaderModule vertShaderModule;
			VkShaderModule fragShaderMoule;
	};
}