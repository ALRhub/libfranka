#include "library_loader.h"

using namespace std::string_literals;  // NOLINT (google-build-using-namespace)

namespace franka {

LibraryLoader::LibraryLoader(const std::string& filepath) {
  try {
    library_.load(filepath + Poco::SharedLibrary::suffix());
  } catch (const Poco::LibraryAlreadyLoadedException& e) {
    throw ModelLibraryException("libfranka: model library already loaded"s);
  } catch (const Poco::NotFoundException& e) {
    throw ModelLibraryException("libfranka: symbol cannot be found: "s +
                                e.what());
  } catch (const Poco::LibraryLoadException& e) {
    throw ModelLibraryException("libfranka: cannot load model library: "s +
                                e.what());
  } catch (const Poco::Exception& e) {
    throw ModelLibraryException("libfranka: error while loading library: "s +
                                e.what());
  }
}

LibraryLoader::~LibraryLoader() {
  try {
    library_.unload();
  } catch (...) {
  }
}

void* LibraryLoader::getSymbol(const std::string& symbol_name) {
  try {
    return library_.getSymbol(symbol_name);
  } catch (const Poco::NotFoundException& e) {
    throw ModelLibraryException("libfranka: symbol cannot be found: "s +
                                e.what());
  } catch (const Poco::Exception& e) {
    throw ModelLibraryException("libfranka: error while fetching symbols: "s +
                                e.what());
  }
}

}  // namespace franka