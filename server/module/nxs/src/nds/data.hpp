#ifndef NDS_DATA_H_NDS
#define NDS_DATA_H_NDS

#include <vector>

namespace nds
{
    class data
    {
    private:
        std::vector<char> _data;

    public:
        template<class T>
        data(const T&);

        template<class T>
        T get() const;
    };


} // nds
#endif // NDS_DATA_H_NDS
