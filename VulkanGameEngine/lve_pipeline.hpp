#pragma once

#include "lve_device.hpp"   
#include <vector>
#include <string>

namespace lve {
	class LvePipeline {
		public:
			LvePipeline(const std::string& vertFilepath, const std::string& fragFilePath);

		private:
			static std::vector<char> readFile(const std::string& filepath);

			void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilePath);
	};
}