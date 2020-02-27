#pragma once

#include <iostream>

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window {
public:
    /// Ctor
    HelloWorld() {
        set_border_width(10);
        set_title("Goblin Window");
        // Use Lambdas! Not stupid connects from the tutorial
        btn.signal_clicked().connect([]()->void {
            std::cout << "Goblin button pushed !!!" << std::endl;
        });
        add(btn);
        btn.show();
    }
    
protected:
    Gtk::Button btn{"Goblin Button"};
};
