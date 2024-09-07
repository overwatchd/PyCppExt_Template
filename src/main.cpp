#include <pybind11/pybind11.h>
#include <fmt/format.h>
#include "config.h"

namespace py = pybind11;

PYBIND11_MODULE(PROJECT_NAME, m) {
	m.def("version", []() {
		return fmt::format("Version {}.{}", PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR);
	});
}
