#pragma once
//---------------------------------------------------------------------------
#include <valarray>
#include <memory>
#include <functional>
#include <thread>
//---------------------------------------------------------------------------
template <typename T>
class SnapValue {
    public:
        SnapValue(T value_ = 0, long label_ = 0, std::valarray<T> snap_ = std::valarray<T>()) : 
            value(value_), label(label_), snap(snap_) 
            { ; }
        
        SnapValue(const SnapValue& snap_) :
            value(snap_.value), label(snap_.label), snap(snap_.snap)
            { ; }

        T getValue() const {
            return value;
        }

        long getLabel() const {
            return label;
        }

        std::valarray<T> getSnap() const {
            return snap;
        }
    
    private:
        T value;
        long label;
        std::valarray<T> snap;
};
//---------------------------------------------------------------------------
template <typename T>
class Snapshot {
    public: 
        Snapshot(size_t n) : size(n) {
            snapShots = new SnapValue<T>[size];
        }

        ~Snapshot() {
            // delete snapShots;
        }

        void update(T value, size_t tid) {
            std::valarray<T> snap = scan();
            SnapValue<T> oldValue = snapShots[tid];
            SnapValue<T> newValue = SnapValue<T>(value, oldValue.getLabel()+1, snap);
            snapShots[tid] = newValue;
        }

        std::valarray<T> scan() {
            SnapValue<T>* oldCopy;
            SnapValue<T>* newCopy;
            std::valarray<bool> moved(size, false);
            oldCopy = collect();

            while (true) {
                newCopy = collect();
                bool flag = false;
                
                for (size_t i = 0; i < size; ++i) {
                    if (oldCopy[i].getLabel() != newCopy[i].getLabel()) {
                        if (moved[i])
                            return oldCopy[i].getSnap();
                        else {
                            moved[i] = true;
                            flag = true;
                            delete[] oldCopy;
                            oldCopy = newCopy;
                            break;
                        }
                    }
                }
                if (flag)
                    continue;

                std::valarray<T> ret = std::valarray<T>(size);
                for (size_t i = 0; i < size; ++i)
                    ret[i] = newCopy[i].getValue();
                return ret;
            }
        }

    private:
        SnapValue<T>* snapShots;
        size_t size;

        SnapValue<T>* collect() {
            SnapValue<T>* copy = new SnapValue<T>[size];
            for (size_t i = 0; i < size; ++i)
                copy[i] = snapShots[i];
            return copy;
        }

};