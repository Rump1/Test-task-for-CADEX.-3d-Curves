#pragma once

struct Point // Структура для возврата точки или вектора
{
    float x;
    float y;
    float z;

    void print_Point();
};

class Base_curve // Базовый класс для других кривых
{
public:
    virtual Point get_3d_point(float t);
    virtual Point get_first_derivative(float t);
    virtual float get_radius() { return 0; }
    virtual float get_x0() { return 0; }
    virtual float get_y0() { return 0; }
    virtual float get_step() { return 0; }
    virtual float get_second_radius() { return 0; }
};
class Circle : public Base_curve // Окружность
{
private:
    float radius, x0, y0;
public:
    Circle(float radius, float x0, float y0);
    Point get_3d_point(float t);
    Point  get_first_derivative(float t);
    float get_radius() { return radius; }
    float get_x0() { return x0; }
    float get_y0() { return y0; }
}; 

class Ellipse : public Base_curve
{
private:
    float radius, x0, y0, second_radius; // Второй радиус
public:
    Ellipse(float radius, float second_radius, float x0, float y0); // Конструктор
    Point get_3d_point(float t); 
    Point get_first_derivative(float t);
    float get_raduis() { return radius; }
    float get_second_radius() { return second_radius; }
    float get_x0() { return x0; }
    float get_y0() { return y0; }
};

class Helix : public Base_curve // Спираль(винтовая линия)
{
private:
    float radius, step, x0, y0;
public:
    Helix(float radius, float step, float x0, float y0); // Конструктор
    Point get_3d_point(float t);
    Point get_first_derivative(float t);
    float get_radius() { return radius; }
    float get_step() { return step; }
    float get_x0() { return x0; }
    float get_y0() { return y0; }
};
