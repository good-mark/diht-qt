#ifndef WIDGETS_H
#define WIDGETS_H

#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>


struct Object : public QObject
{
    bool isWidget;
    const char* app_class_name;
};


typedef void (*button_click_func)(Object*);

struct Widget : public Object
{
public:
    QWidget* ptr;
    std::vector<Widget*> children;
    Widget();

    Widget(Widget* widget);
};

struct Application : public Object
{
public:
    QApplication* ptr;
    char** fake;
    Application();
};

struct Layout : public Object
{
public:
    QVBoxLayout* ptr;
    Layout(Widget* widget);
};

struct Label : public Widget
{
public:
    //QLabel* ptr;
    Label(Widget* widget);
};

struct PushButton : public Widget
{
private:
    Q_OBJECT

public:
    //QPushButton* ptr;
    /*PushButton(QWidget *parent = 0) :
        QPushButton(parent)
    {
        connect(this,
                SIGNAL(buttonClicked(void (*f)(Object*))),
                this,
                SLOT(handleButtonClicked(void (*h)(Object*)))
                );
    }*/
    ~PushButton();
    button_click_func myfunc;

    explicit PushButton(Widget* widget);

public Q_SLOTS:
    void handleButtonClicked();

};




const char* Object_GetClassName(Object* object);

Application* Application_New();

Widget* Widget_New(Widget* widget);

Layout* VBoxLayout_New(Widget* widget);

Label* Label_New(Widget* widget);

PushButton* PushButton_New(Widget* widget);


void Widget_SetLayout(Widget* widget, Layout* layout);

void Label_SetText(Label* label, const QString& txt);

void Layout_AddWidget(Layout* layout, Widget* label);

void PushButton_SetText(PushButton* button, const QString& txt);

void Widget_SetWindowTitle(Widget* widget, const QString& txt);

void Widget_SetSize(Widget* widget, int x, int y);

void Widget_SetVisible(Widget* widget, bool flag);

int Application_Exec(Application* app);

void Object_Delete(Object* object);

void PushButton_SetOnClicked(PushButton* button, button_click_func handle_button_click);

#endif // WIDGETS_H
