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
#include <iostream>
#include <vector>
#include <cmath>
#include <typeinfo>
using namespace std;



class Circle // Окружность
{
protected: 
    float radius, x0, y0;
public:
    virtual vector<float> get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
    {
        vector<float> point(3);
        point[0] = radius * cos(t) + x0;
        point[1] = radius * sin(t) + y0;
        point[2] = 0;
        return point;
    }
    // Формулы для производных->
    /* Производные: от x по t = -r * sin(t),
                    от y по t = r * cos(t),
                    от z по t = 0 по определению 
    */
    virtual vector<float> get_first_derivative(float t) 
    {
        vector<float> derivative(3);
        derivative[0] = -radius * sin(t);
        derivative[1] = radius * cos(t);
        derivative[2] = 0;
        return derivative;
    }
    virtual string identification() // Идентификационный метод, чтобы определить класс по объекту
    {
        return "Circle";
    }
    Circle(float radius, float x0, float y0) : radius(radius), x0(x0), y0(y0) {} // Список инициализации конструктора
    virtual float get_radius()
    {
        return radius;
    }
};

class Ellipse : public Circle // Эллипс наследуется от окружности
{
private:
    float second_radius; // Второй радиус
public:
    Ellipse(float radius, float second_radius, float x0, float y0) 
        : Circle(radius, x0, y0), second_radius(second_radius) {} // Конструктор
    
    vector<float> get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
    {
        vector<float> point(3);
        point[0] = radius * cos(t) + x0;
        point[1] = second_radius * sin(t) + y0;
        point[2] = 0;
        return point;
    }
    // Формулы для производных->
    /* Производные: от x по t = -radius * sin(t),
                    от y по t = second_radius * cos(t),
                    от z по t = 0 по определению
    */
    vector<float> get_first_derivative(float t)
    {
        vector<float> derivative(3);
        derivative[0] = -radius * sin(t);
        derivative[1] = second_radius * cos(t);
        derivative[2] = 0;
        return derivative;
    }
    string identification()
    {
        return "Ellipse";
    }
};

class Helix : public Circle // Спираль(винтовая линия) наследуется от окружности
{
private:
    float step;
public:
    Helix(float radius, float step, float x0, float y0) : Circle(radius, x0, y0), step(step) {} // Конструктор

    vector<float> get_3d_point(float t) // Высчитываем координаты точки по формуле, создаем вектор, возвращаем
    {
        vector<float> point(3);
        point[0] = radius * cos(t) + x0;
        point[1] = radius * sin(t) + y0;
        point[2] = step * t / (2 * M_PI); // Так как step = 2 * b * pi, => b = step / (2 * pi)
        return point;
    }
    // Формулы для производных->
    /* Производные: от x по t = -r * sin(t), 
                    от y по t = r * cos(t),
                    от z по t = b 
    */
    vector<float> get_first_derivative(float t)
    {
        vector<float> derivative(3);
        derivative[0] = -radius * sin(t);
        derivative[1] = radius * cos(t);
        derivative[2] = step / (2 * M_PI);
        return derivative;
    }
    string identification()
    {
        return "Helix";
    }
};


int main()
{
    setlocale(LC_ALL, "ru");
    vector<shared_ptr<Circle>> curves;
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
        vector<float> point = curves[i]->get_3d_point(t);
        vector<float> derivative = curves[i]->get_first_derivative(t);
        cout << "{" << point[0] << "  " << point[1] << "  " << point[2] << "}  {" 
               << derivative[0] << "  " << derivative[1] << "  " << derivative[2] << "}\n";
    }
    
    vector<shared_ptr<Circle>> only_circles; // Массив для кружков
    for (int i = 0; i < curves_size; ++i) // Заполнение второго вектора только кружочками
    {
        if (curves[i]->identification() == "Circle") // Если в массиве наткнулись на круг
        {
            only_circles.push_back(curves[i]); // Добавляем в другой массив указатель на тот же элемент
        }
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
