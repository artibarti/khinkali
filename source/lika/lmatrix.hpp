
#ifndef LIKA_MATRIX_H
#define LIKA_MATRIX_H

namespace Lika
{
    template<typename T, int V, int H>
    class Matrix
    {
        private:
            int size_h = H;
            int size_v = V;
            std::vector<T> values;

        public:
            Matrix();
            Matrix(std::initializer_list<std::initializer_list<T>> il);
            Matrix(T t);

            Matrix<T,V,H> operator=(Matrix<T,V,H> m);
            Matrix<T,V,H> operator+(Matrix<T,V,H> m);
            Matrix<T,V,H> operator-(Matrix<T,V,H> m);

            Matrix<T,H,V> transpose();
            Matrix<T,V,H> fillWithZeros();
            Matrix<T,V,H> fillWith(T t);

            void showInfo();
    };

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix()
    {
        for(int i = 0; i<size_h*size_v; i++)
        {
            values.push_back(0);
        }
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(T t)
    {
        for(int i = 0; i<size_h*size_v; i++)
        {
            values.push_back(t);
        }
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(std::initializer_list<std::initializer_list<T>> il)
    {
        if (il.size() == V && 
            std::all_of(il.begin(), il.end(), [](std::initializer_list<T> ile){return ile.size() == H;}))
        {
            for (auto it = il.begin(); it != il.end(); it++)
                std::move(it->begin(), it->end(), std::back_inserter(values));
        }
		else
			throw std::invalid_argument( "initializer list size does not corresponding fot this type" );            
    }
    
    template<typename T, int V, int H>
    Matrix<T,V,H> Matrix<T,V,H>::fillWithZeros()
    {
        values.clear();

        for (int i = 0; i<size_v*size_h; i++)
        {
            values.push_back(0);
        }

        return *this;
    }

    template<typename T, int V, int H>
    void Matrix<T,V,H>::showInfo()
    {
		std::cout << "Matrix of type " << boost::typeindex::type_id<T>().pretty_name() 
            << " with " << size_v << " rows and " << size_h << " columns" << std::endl;
    
        for (int rows = 0; rows<size_v; rows++)
        {
            for (int cols = 0; cols<size_h; cols++)
            {
                std::cout << values[rows*size_h + cols] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    typedef Matrix<int, 2, 2> mat2x2i;
    typedef Matrix<int, 3, 3> mat3x3i;
    typedef Matrix<int, 4, 4> mat4x4i;

    typedef Matrix<double, 2, 2> mat2x2d;
    typedef Matrix<double, 3, 3> mat3x3d;
    typedef Matrix<double, 4, 4> mat4x4d;

};

#endif