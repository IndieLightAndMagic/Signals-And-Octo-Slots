#ifndef WEAKMAP_H
#define WEAKMAP_H

#include <functional>
#include <memory>
#include <vector>
#include <map>

namespace GTech{

    template <typename V, typename K, typename C>
    class WeakMap {
    protected:
        std::map<K, std::weak_ptr<V>> m {};
        std::shared_ptr<C> sp_context;
        std::function<std::shared_ptr<V>(K, C&)> fresolution;
    public:
        std::shared_ptr<V> operator[](const K& key){
            auto wp_v = m[key];
            auto sp_v = wp_v.lock();
            if (!sp_v){
                sp_v = fresolution(key, *sp_context);
                m[key] = sp_v;
            }
            return sp_v;
        }
         
    };


}

#endif /* WEAKMAP_H */