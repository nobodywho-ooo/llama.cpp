// Test that storing the model and context in a static
// // with C++ constructors/destructors works.

#include "llama-cpp.h"
#include "common.h"

struct llama_backend {
    llama_backend() {
        printf("foo::llama_backend_init\n");
        llama_backend_init();
    }

    ~llama_backend() {
        printf("foo::llama_backend_free\n");
        llama_backend_free();
    }
};

// Initialize the backend at program startup and shutdown,
// by using static constructors/destructors.
static llama_backend backend {};

static llama_model_ptr model;
static llama_context_ptr ctx;

int main(int argc, char ** argv) {
    auto * model_path = common_get_model_or_exit(argc, argv);

    model.reset(llama_model_load_from_file(model_path, llama_model_default_params()));
    ctx.reset(llama_init_from_model(model.get(), llama_context_default_params()));
    // ctx.reset();

    return 0;
}
