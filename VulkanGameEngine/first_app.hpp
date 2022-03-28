#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "lve_model.hpp"

#include <memory>

namespace lve {
	class FirstApp
	{
		public:
			static constexpr int WIDTH = 1920;
			static constexpr int HEIGHT = 1080;

			FirstApp();
			~FirstApp();

			FirstApp(const FirstApp &) = delete;
			FirstApp &operator=(const FirstApp &) = delete;

			void run();

		private:
			void loadModels();
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void freeCommandBuffers();
			void drawFrame();
			void recreateSwapChain();
			void recordCommandbuffer(int imageIndex);

			LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
			LveDevice lveDevice{ lveWindow };
			std::unique_ptr<LveSwapChain> lveSwapChain;
			/*LvePipeline lvePipeline{
				"simple_shader.vert.spv",
				"simple_shader.frag.spv",
				lveDevice,
				LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)
			};*/
			std::unique_ptr<LvePipeline> lvePipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
			std::unique_ptr<LveModel> lveModel;
	};
}