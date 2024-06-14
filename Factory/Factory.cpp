﻿#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
#include<ctime>


using namespace std;

//#define MIN_SIZE		50
//#define MAX_SIZE		800
//#define MIN_LINE_WIDTH	1
//#define MAX_LINE_WIDTH	25
//
//#define MAX_HORIZONTAL_RESOLUTION	800
//#define MAX_VERTICAL_RESOLUTION		600

namespace MyGeometry
{
	enum Color
	{
		RED = 0x000000FF,
		GREEN = 0x0000FF00,
		BLUE = 0x00FF0000,
		GREY = 0x00AAAAAA,
		YELLOW = 0x0000FFFF
	};
#define SHAPE_TAKE_PARAMETERS unsigned int x, unsigned int y, unsigned int line_width, COLORREF color
#define SHAPE_GIVE_PARAMETERS x, y, line_width, color
	class Shape{
	protected:
		unsigned int x;
		unsigned int y;
		unsigned int line_width;
		COLORREF color;
	public:

		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 300;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 25;
		static const int MAX_HORIZONTAL_RESOLUTION = 800;
		static const int MAX_VERTICAL_RESOLUTION = 600;


		unsigned int get_x()const{
			return x;
		}
		unsigned int get_y()const{
			return y;
		}
		unsigned int get_line_width()const{
			return line_width;
		}
		unsigned int set_size(unsigned int size){
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}
		void set_x(unsigned int x){
			this->x = x < MAX_HORIZONTAL_RESOLUTION ? x : MAX_HORIZONTAL_RESOLUTION;
		}
		void set_y(unsigned int y){
			this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
		}
		void set_line_width(unsigned int line_width){
			if (line_width < MIN_LINE_WIDTH)line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH)line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}

		//				Constructors:
		Shape(SHAPE_TAKE_PARAMETERS) :color(color){
			set_x(x);
			set_y(y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		//				Methods:
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		

		


		
		void draw()const {

			

			HWND hwnd = GetConsoleWindow();	//Получаем дескриптор окна консоли.



			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);	//Карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);	//Кисть заливает фигуру


			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			ShapeTipe(hdc);



			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);

		}
		virtual void ShapeTipe(HDC& hdc)const=0;
		virtual void info()const{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}

	};

	class Rectangle :public Shape{
		double width;
		double height;
	public:
		double get_width()const{
			return width;
		}
		double get_height()const{
			return height;
		}
		void set_width(double width){
			this->width = set_size(width);
		}
		void set_height(double height){
			this->height = set_size(height);
		}

		//				Constructors:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS){
			set_width(width);
			set_height(height);
			
		}
		~Rectangle() {}
		
		//				Methods:
		double get_area()const override{
			return width * height;
		}
		double get_perimeter()const override{
			return (width + height) * 2;
		}
		void ShapeTipe(HDC& hdc)const override {

			::Rectangle(hdc, x, y, x + width, y + height);
		}
		void info()const override{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << width << endl;
			cout << "Высота: " << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle{


	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		~Square() {}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const{
			return radius;
		}
		double get_diameter()const{
			return 2 * radius;
		}
		double get_area()const override{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override{
			return M_PI * get_diameter();
		}
		void set_radius(double radius){
			this->radius = set_size(radius);

		}
		void ShapeTipe(HDC& hdc)const override {

			::Ellipse(hdc, x, y, x + get_diameter(), y + get_diameter());
		}
		//				Constructors:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS){
			set_radius(radius);
		}
		~Circle() {}
		
		
	};
	/* namespace shapes{
	 
		 enum Shapes
		 {
			 Rectangle, Square, Circle
		 };
	 }


	class Shape_Factory {
	public:

		static Shape* createShape(shapes::Shapes type) {
			
				Shape* shape = nullptr;
#define SHAPE_PARAMETERS rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,rand() % Shape::MAX_LINE_WIDTH,RGB(rand(), rand(), rand())
				switch (type)
				{
				case 0:	shape = new Rectangle
					  (
						  rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE,
						  rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,
						  rand() % Shape::MAX_LINE_WIDTH,
						  RGB(rand(), rand(), rand())
					  );
					break;
				case 1: shape = new Square(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
				case 2: shape = new Circle(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
				}
				return shape;
		}

	};*/
	Shape* ShapeFactory(int shape_id)
	{
		Shape* shape = nullptr;
#define SHAPE_PARAMETERS rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,rand() % Shape::MAX_LINE_WIDTH,RGB(rand(), rand(), rand())
		switch (shape_id)
		{
		case 1:	shape = new Rectangle
			  (
				  rand() % Shape::MAX_SIZE, rand() % Shape::MAX_SIZE,
				  rand() % Shape::MAX_HORIZONTAL_RESOLUTION, rand() % Shape::MAX_VERTICAL_RESOLUTION,
				  rand() % Shape::MAX_LINE_WIDTH,
				  RGB(rand(), rand(), rand())
			  );
			break;
		case 2: shape = new Square(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
		case 3: shape = new Circle(rand() % Shape::MAX_SIZE, SHAPE_PARAMETERS); break;
		}
		return shape;
	}



	class NewBilder {

	public:


		NewBilder() {}
		Square* builder_Square() {
			return new Square(100, 250, 250, 8, RGB(225, 225, 225));
			
		}
		Rectangle* builder_Rectangle() {
			return new Rectangle (150,75, 60, 250, 8, RGB(225, 225, 225));
		}
		Circle* builder_Circle() {
			return new Circle(100, 250, 250, 8, RGB(225, 225, 225));
		}
		~NewBilder() {};
	};



}



//#define USING_ENUM_COLOR
//#define USING_COLORREF

void main()
{
	setlocale(LC_ALL, "");
#ifdef USING_ENUM_COLOR
	MyGeometry::Rectangle rect(100, 50, 350, 100, 8, MyGeometry::Color::RED); 
	
	rect.info(); 

	MyGeometry::Square square(44, 550, 100, 5, MyGeometry::Color::GREY);  
	square.info(); 

	MyGeometry::Circle circle(75, 750, 100, 5, MyGeometry::Color::YELLOW);
	circle.info();
#endif // ENUM_COLOR

#ifdef USING_COLORREF
	MyGeometry::Rectangle rect(100, 50, 350, 100, 8, RGB(255, 0, 0));
	
	rect.info();

	MyGeometry::Square square(44, 550, 100, 5, RGB(0, 0, 255));
	square.info();

	MyGeometry::Circle circle(75, 750, 100, 5, RGB(255, 255, 0));
	circle.info();
#endif // USING_COLORREF

	/*srand(time(NULL));
	const int coll = 15;
	MyGeometry::Shape* shape[coll]{};
	for (int i = 0; i < coll; i++)
	{
		MyGeometry::Shape_Factory::createShape(static_cast<MyGeometry::shapes::Shapes>(rand() % 3));
	}

	for (int i = 0; i < coll; i++)
	{
		shape[i]->draw();
		Sleep(500);
	}*/

	/*srand(time(NULL));
	const int coll  = 100;
	MyGeometry::Shape* shape[coll]{};
	for (int i = 0; i < coll; i++)
	{
		shape[i] = MyGeometry::ShapeFactory(rand() % 3 + 1);
	}

	for (int i = 0; i < coll; i++)
	{
		shape[i]->draw();
		Sleep(500);
	}

	for (int i = 0; i < coll; i++)delete[] shape[i];*/
	
	MyGeometry::NewBilder bilder1;
	MyGeometry::Shape* pointer= bilder1.builder_Rectangle();
	pointer->info();
	
	
	
	
}