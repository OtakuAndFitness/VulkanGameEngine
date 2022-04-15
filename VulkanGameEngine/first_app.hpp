#pragma once

#include "lve_window.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"

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
			void loadGameObjects();

			LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
			LveDevice lveDevice{ lveWindow };
			LveRenderer lveRenderer{ lveWindow, lveDevice };
			std::vector<LveGameObject> gameObjects;
	};
}