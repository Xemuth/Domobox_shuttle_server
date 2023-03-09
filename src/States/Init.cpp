#include "Definition.hpp"
#include "State.hpp"

namespace
{
    void hello()
    {
        printf("Hello world !\n");
    }
}

namespace domobox
{
    struct State::StateImpl
    {
        int a;
    };

    const char* State::name()
    {
        return "Initialisation";
    }

    Error State::run()
    {
        hello();
        return Error::fake_error;
    }

    std::shared_ptr<State::StateImpl> make_init()
    {
        return std::make_shared<State::StateImpl>();
    }
}