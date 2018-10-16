
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
            std::vector<std::vector<T>> values;

        public:
            Matrix();
            Matrix(std::initializer_list<std::initializer_list<T>> il);
            Matrix(T t);

            std::vector<std::vector<T>> getValues() const;
            T get(int row_index, int col_index) const;
            std::vector<T>& operator[] (int index);

            Matrix<T,V,H>& operator=(const Matrix<T,V,H>& m);
            Matrix<T,V,H> operator+(const Matrix<T,V,H>& m);
            Matrix<T,V,H> operator-(const Matrix<T,V,H>& m);

            Matrix<T,H,V> transpose();
            Matrix<T,V,H>& fillWithZeros();
            Matrix<T,V,H>& fillWith(T t);

            void showInfo();
    };

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix()
    {
        fillWithZeros();
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(T t)
    {
        fillWith(t);
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(std::initializer_list<std::initializer_list<T>> il)
    {
        if (il.size() == V && 
            std::all_of(il.begin(), il.end(), [](std::initializer_list<T> ile){return ile.size() == H;}))
        {
            values.clear();
            for (auto it = il.begin(); it != il.end(); it++)
            {
                std::vector<T> row_vec;
                std::move(it->begin(), it->end(), std::back_inserter(row_vec));
                values.push_back(row_vec);
            }
        }
		else
			throw std::invalid_argument( "initializer list size does not corresponding fot this type" );            
    }

    template<typename T, int V, int H>
    std::vector<std::vector<T>> Matrix<T,V,H>::getValues() const
    {
        return values;
    }

    template<typename T, int V, int H>
    T Matrix<T,V,H>::get(int row_index, int col_index) const
    {
        return values[row_index][col_index];
    }

    template<typename T, int V, int H>
    std::vector<T>& Matrix<T,V,H>::operator[] (int index)
    {
        return values[index];
    }


    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::fillWithZeros()
    {
        values.clear();

        for (int rows = 0; rows < size_v; rows++)
        {
            std::vector<T> row_vec;
            for (int cols = 0; cols < size_h; cols++)
            {
                row_vec.push_back(0);
            }
            values.push_back(row_vec);
        }

        return *this;
    }
    
    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::fillWith(T t)
    {
        values.clear();

        for (int rows = 0; rows < size_v; rows++)
        {
            std::vector<T> row_vec;
            for (int cols = 0; cols < size_h; cols++)
            {
                row_vec.push_back(t);
            }
            values.push_back(row_vec);
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
                std::cout << values[rows][cols] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::operator=(const Matrix<T,V,H>& m)
    {
        values.clear;
        std::copy(m.getValues().begin(), m.getValues().end(), std::back_inserter(values));
        return *this;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H> Matrix<T,V,H>::operator+(const Matrix<T,V,H>& m)
    {
        Matrix<T,V,H> result;
        
        for (int row = 0; row < size_v; row++)
        {
            for (int col = 0; col < size_h; col++)
            {
                (result[row])[col] = m.get(row,col) + get(row,col);
            }
        }

        return result;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H> Matrix<T,V,H>::operator-(const Matrix<T,V,H>& m)
    {
        Matrix<T,V,H> result;
        
        for (int row = 0; row < size_v; row++)
        {
            for (int col = 0; col < size_h; col++)
            {
                (result[row])[col] = get(row,col) - m.get(row,col);
            }
        }

        return result;
    }

    typedef Matrix<int, 2, 2> mat2x2i;
    typedef Matrix<int, 3, 3> mat3x3i;
    typedef Matrix<int, 4, 4> mat4x4i;

    typedef Matrix<double, 2, 2> mat2x2d;
    typedef Matrix<double, 3, 3> mat3x3d;
    typedef Matrix<double, 4, 4> mat4x4d;

};

#endif