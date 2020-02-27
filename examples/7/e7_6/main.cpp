// Example 7.6 gtkmm
// 2020 by Oleksiy Grechnyev

#include <gtkmm/application.h>

#include "./HelloWorld.h"

int main(int argc, char** argv)
{
        auto app = Gtk::Application::create(argc, argv, "org.brianna.love");
        
        HelloWorld hw;
        
        return app->run(hw);
}
