#include <QCoreApplication>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;
template<typename In, typename Out>
class Monada;
template<typename T>
class myVector
{
public:
    list<T> myData;
    static int linear_solve(list<T> vec, T find)
    {
        if(vec.size() == 0 )
        {
            return -1;
        }

        if(vec.front() == find)
        {
            return 0;
        }
        else
        {
            list<T> newVec = vec;
            newVec.pop_front();
            const int answer = Monada<T, int>::m_return(&newVec, find, linear_solve);
            if(answer == -1)
            {
                return -1;
            }
            else
            {
                return answer + 1;
            }
        }
    }
    static list<T> sort(list<T>  vec)
    {
        if(vec.size() == 1)
        {
            return vec;
        }
        pair<int,T> minimal = findSmalest(vec);
        list<T> newList = vec;

            auto iter = newList.begin();
        for(int i = 0; i < minimal.first; i++)
            iter++;

        std::swap(*newList.begin(),*iter);
        newList.pop_front();
        auto ret= [=] (){
                auto sorted = sort(newList);
                sorted.push_front(minimal.second);
                return sorted;
        };
        return ret();

    }
    static pair<int, int> findSmalest(const list<T> vec)
    {
        if(vec.size() == 1)
        {
            return make_pair(0, vec.front());
        }
        auto newVec = vec;
        newVec.pop_front();
        pair<int,int> answer = findSmalest(newVec);
        if(answer.second < vec.front())
        {
            return make_pair(answer.first + 1, answer.second);
        }
        else
        {
            return make_pair(0, vec.front());
        }
    }
};

template<typename In, typename Out>
class Monada
{
public:
    static Out m_return(list<In> *input, In find, std::function<Out(list<In>, In)> f)
    {
        if (!input && !find)return (Out)0;

        return f(*input, find);
    }
};

int main()
{

    myVector<int> vec;
    vec.myData = {9, 6, 5, 7};
   while(1)
   {
    cout << "Enter element: \n";
    int a;
    cin >> a;
    cout << "Result : " << Monada<int, int>::m_return(&vec.myData, a, &myVector<int>::linear_solve) << endl;
    cout << myVector<int>::findSmalest(vec.myData).first << " " << myVector<int>::findSmalest(vec.myData).second << endl;
    auto sorted =  myVector<int>::sort(vec.myData);
    foreach (auto el, sorted) {
        cout<< "\t " << el;
    }
   }
    return 0;
}
