#include "widgets.h"
Widget::Widget()
{
    app_class_name = "Widget";
    ptr = new QWidget();
    isWidget = true;
}

Widget::Widget(Widget* widget)
{
    app_class_name = "Widget";
    ptr = new QWidget(widget->ptr);
    widget->children.push_back(this);
    isWidget = true;
}

Application::Application()
{
    app_class_name = "Application";
    int arg = 0;
    char* fakestr = new char[1];
    fake = &fakestr;
    ptr = new QApplication(arg, this->fake);
}

Layout::Layout(Widget* widget)
{
    app_class_name = "VBoxLayout";
    ptr = new QVBoxLayout(widget->ptr);
}

Label::Label(Widget* widget)
{
    app_class_name = "Label";
    ptr = new QLabel(widget->ptr);
}

PushButton::~PushButton() {}

PushButton::PushButton(Widget* widget)
{
    app_class_name = "PushButton";
    ptr = new QPushButton(widget->ptr);
    connect(this,
            SIGNAL(clicked(bool)),
            this,
            SLOT(handleButtonClicked())
            );
}

void PushButton::handleButtonClicked()
{
    myfunc((Object*) this);
}




const char* Object_GetClassName(Object* object)
{
    return object->app_class_name;
}

Application* Application_New()
{
    return new Application();
}

Widget* Widget_New(Widget* widget)
{
    if (widget == NULL)
        return new Widget();
    return new Widget(widget);
}

Layout* VBoxLayout_New(Widget* widget)
{
    return new Layout(widget);
}

Label* Label_New(Widget* widget)
{
    return new Label(widget);
}

PushButton* PushButton_New(Widget* widget)
{
    return new PushButton(widget);
}


void Widget_SetLayout(Widget* widget, Layout* layout)
{
    widget->ptr->setLayout(layout->ptr);
}

void Label_SetText(Label* label, const QString& txt)
{
    ((QLabel*) label->ptr)->setText(txt);
}

void Layout_AddWidget(Layout* layout, Widget* label)
{
    layout->ptr->addWidget(label->ptr);
}

void PushButton_SetText(PushButton* button, const QString& txt)
{
    ((QPushButton*) button->ptr)->setText(txt);
}

void Widget_SetWindowTitle(Widget* widget, const QString& txt)
{
    widget->ptr->setWindowTitle(txt);
}

void Widget_SetSize(Widget* widget, int x, int y)
{
    widget->ptr->resize(x, y);
}

void Widget_SetVisible(Widget* widget, bool flag)
{
    widget->ptr->setVisible(flag);
}

int Application_Exec(Application* app)
{
    return app->ptr->exec();
}

void Object_Delete(Object* object)
{
    if (object->isWidget)
    {
        Widget* widget = (Widget*) object;
        std::vector<Widget*>::iterator it = widget->children.begin();
        for (; it != widget->children.end(); ++it)
        {
            Object_Delete(*it);
        }
        delete(widget->ptr);
        delete(widget);
    }
    else
    {
        delete(object);
    }
}

void PushButton_SetOnClicked(PushButton* button, button_click_func handle_button_click)
{
    //button->handleButtonClicked(handle_button_click);
    button->myfunc = handle_button_click;
    //button-> buttonClicked(handle_button_click);
    //handle_button_click((Object*) button);
}

