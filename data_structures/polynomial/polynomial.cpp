#include <iostream>
#include <vector>

struct Polynomial
{
    std::vector<double> coef{};
    int degree{};
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << '[';
    for (size_t i = 0; i < v.size(); ++i)
    {
        out << v[i];
        if (i != v.size() - 1)
        {
            out << ", ";
        }
    }
    out << "]\n";
    return out;
}

std::vector<double> polyadd(const std::vector<double> &p, const std::vector<double> &q)
{
    // The '>=' condition ensures correctness even when p and q have equal sizes,
    // as it guarantees that one vector is consistently treated as the 'larger' one.
    const std::vector<double> &larger = p.size() >= q.size() ? p : q;
    const std::vector<double> &smaller = p.size() < q.size() ? p : q;
    int size_diff = larger.size() - smaller.size();
    std::vector<double> result{larger};

    for (size_t i = 0; i < smaller.size(); ++i)
    {
        result[i + size_diff] += smaller[i];
    }

    return result;
}

std::vector<double> polysub(const std::vector<double> &p, const std::vector<double> &q)
{
    int size_diff = std::max(p.size(), q.size()) - std::min(p.size(), q.size());

    if (p.size() >= q.size())
    {
        std::vector<double> result{p};
        for (size_t i = 0; i < q.size(); ++i)
        {
            result[i + size_diff] -= q[i];
        }
        return result;
    }
    else
    {
        std::vector<double> result{q};
        for (size_t i = 0; i < p.size(); ++i)
        {
            result[i + size_diff] = p[i] - result[i + size_diff];
        }
        return result;
    }
}

int main()
{
    std::vector<double> p{      4, 3};
    std::vector<double> q{   3, 8, 7};

    std::cout << polyadd(p, q);
    std::cout << polysub(p, q);
}
