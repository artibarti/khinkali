
#ifndef LIKA_MATRIX_H
#define LIKA_MATRIX_H

namespace Lika
{
    template<typename T, int SIZE_H, int SIZE_V>
    class Matrix
    {
        private:
            int size_h = SIZE_H;
            int size_v = SIZE_V;
            std::vector<T> values;

        public:
            Matrix();
    };

};

#endif