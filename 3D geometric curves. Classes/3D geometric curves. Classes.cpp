// 3D geometric curves. Classes.cpp 
// Формулы:
/* 
    Для круга - x = r * cos(t) + x0 , где (x0, y0) - координаты центра окружности
                y = r * sin(t) + y0

    Для эллипса - x = a * cos(t) + x0 , где (x0, y0) - координаты центра, a и b - радиусы
                  y = b * sin(t) + y0

    Для винтовой линии - x = r * cos(t) + x0 , где (x0, y0) - координаты центра, 2 * b * pi - шаг линии
                         y = r * sin(t) + y0
                         z = b * t
*/ 
#define _USE_MATH_DEFINES  // Для константы pi
#include "Header.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <typeinfo>
using namespace std;

void Point::print_Point()
{
    cout << "{ " << x << ", " << y << ", " << z << " }";
}

Point Base_curve::get_3d_point(float t)
{
    Point point;
    point.x = 0; point.y = 0; point.z = 0;
    return point;
}
Point Base_curve::get_first_derivative(float t)
{
    Point point;
    point.x = 0; point.y = 0; point.z = 0;
    return point;
}

Circle::Circle(float radius, float x0, float y0) : radius(radius), x0(x0), y0(y0) {} // Конструктор круга
Point Circle::get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
{
    Point point;
    point.x = radius * cos(t) + x0;
    point.y = radius * sin(t) + y0;
    point.z = 0;
    return point;
}
Point Circle::get_first_derivative(float t) // Производная для круга
{
    Point derivative;
    derivative.x = -radius * sin(t);
    derivative.y = radius * cos(t);
    derivative.z = 0;
    return derivative;
}

Ellipse::Ellipse(float radius, float second_radius, float x0, float y0) : radius(radius), second_radius(second_radius), x0(x0), y0(y0) {} // Конструктор круга
Point Ellipse::get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
{
    Point point;
    point.x = radius * cos(t) + x0;
    point.y = second_radius * sin(t) + y0;
    point.z = 0;
    return point;
}
Point Ellipse::get_first_derivative(float t) // Производная для круга
{
    Point derivative;
    derivative.x = -radius * sin(t);
    derivative.y = second_radius * cos(t);
    derivative.z = 0;
    return derivative;
}

Helix::Helix(float radius, float step, float x0, float y0) : radius(radius), step(step), x0(x0), y0(y0) {} // Конструктор круга
Point Helix::get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
{
    Point point;
    point.x = radius * cos(t) + x0;
    point.y = radius * sin(t) + y0;
    point.z = step * t / (2 * M_PI);
    return point;
}
Point Helix::get_first_derivative(float t) // Производная для круга
{
    Point derivative;
    derivative.x = -radius * sin(t);
    derivative.y = radius * cos(t);
    derivative.z = step / (2 * M_PI);
    return derivative;
}


int main()
{
    setlocale(LC_ALL, "ru");
    vector<shared_ptr<Base_curve>> curves;
    srand(time(NULL));
    cout.precision(1); // Установка вывода с одним знаком после запятой
    cout.setf(ios::fixed);

    /* Заполнение вектора случайными объектами со случайными параметрами , 20 элементов
    Радиусы от 1 до 100, координаты центра от - 50 до 49, шаг спирали от 1 до 10 */
    for (int i = 0; i < 20; ++i) 
    {
        switch (rand() % 3)
        {
        case 0: curves.push_back(make_shared<Circle>(rand() % 100 + 1, rand() % 100 - 50, rand() % 100 - 50)); break;
        case 1: curves.push_back(make_shared<Ellipse>(rand() % 100 + 1, rand() % 100 + 1, rand() % 100 - 50, rand() % 100 - 50)); break;
        case 2: curves.push_back(make_shared<Helix>(rand() % 100 + 1, rand() % 10 + 1, rand() % 100 - 50, rand() % 100 - 50)); break;
        }
    }

   // Рассчет и вывод точек и производных на экран
    cout << "Координаты точек и значения производных при t = pi/4:\n      Точки:\t      Производные:\n";
    float t = M_PI_4;
    //const auto& curve : curves могло быть внутри цикла
    int curves_size = curves.size();
    for (int i = 0; i < curves_size; ++i)
    {
        Point point = curves[i] -> get_3d_point(t);
        Point derivative = curves[i]->get_first_derivative(t);
        point.print_Point();
        cout << "  ";
        derivative.print_Point();
        cout << "\n";
    }
    
    vector<shared_ptr<Base_curve>> only_circles; // Массив для кружков
    for (int i = 0; i < curves_size; ++i) // Заполнение второго вектора только кружочками

        if (dynamic_pointer_cast<Circle>(curves[i]) != nullptr) // Если в массиве наткнулись на круг
        {
            only_circles.push_back(curves[i]); // Добавляем в другой массив указатель на тот же элемент
        }
    

    // Сортировка массива кружков реализована методом пузырька
    int only_circles_size = only_circles.size();
    for (int i = 0; i < only_circles_size - 1; ++i)
    {
        for (int j = 0; j < only_circles_size - i - 1; ++j)
        {
            if (only_circles[j]->get_radius() > only_circles[j + 1]->get_radius()) // Если радиус больше
            {
                // Меняем элементы местами
                swap(only_circles[j], only_circles[j + 1]);
            }
        }
    }

    float radius_sum = 0;
    cout << "\nРадиусы кружков после сортировки:\n";
    for (int i = 0; i < only_circles_size; ++i)
    {
        float cur_radius = only_circles[i]->get_radius();
        radius_sum += cur_radius;
        cout << cur_radius << "  ";
    }
    cout << "\n\nСуммарный радиус всех кривых во втором массиве: " << radius_sum << "\n\n";
}
