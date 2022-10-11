#pragma once
//---------------------------------------------------------------------------
#include <valarray>
#include <memory>
#include <functional>
#include <thread>
//---------------------------------------------------------------------------
template <typename T>
// Container to store snap with label and value
// MRSW register
class SnapValue {
    public:
        // Constructor with value, label and snap
        SnapValue(T value_ = 0, long label_ = 0, std::valarray<T> snap_ = std::valarray<T>()) : 
            value(value_), label(label_), snap(snap_) 
            { ; }
        
        // Constructor to copy other snap
        SnapValue(const SnapValue& snap_) :
            value(snap_.value), label(snap_.label), snap(snap_.snap)
            { ; }

        // Getter for value
        T getValue() const {
            return value;
        }

        // Getter for label
        long getLabel() const {
            return label;
        }

        // Getter for snap
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
// Class for wait-free snapshot
class Snapshot {
    public:
        // Constructor with size n(#threads)
        Snapshot(size_t n) : size(n) {
            snapShots = new SnapValue<T>[size];
        }

        // Default destructor
        ~Snapshot() {
            // delete snapShots;
        }

        // Update thread local value for thread id with clean snapshot
        void update(T value, size_t tid) {
            // Get clean snap before update
            std::valarray<T> snap = scan();
            // Load old snapshot to get previous label
            SnapValue<T> oldValue = snapShots[tid];
            // Make new snapshot with updated label
            // Wrap-around may be needed for increasing label
            SnapValue<T> newValue = SnapValue<T>(value, oldValue.getLabel()+1, snap);
            // Save new snapshot for other threads to scan
            snapShots[tid] = newValue;
        }

        // Get clean snapshot
        std::valarray<T> scan() {
            // Containers for scan
            SnapValue<T>* oldCopy;
            SnapValue<T>* newCopy;
            std::valarray<bool> moved(size, false);

            // Get first snap
            oldCopy = collect();

            while (true) {
                // Get another snap to compare
                newCopy = collect();

                // Flag which set to true when another collect needed
                bool flag = false;
                
                // Compare with each thread's snapshots
                for (size_t i = 0; i < size; ++i) {
                    // Compare labels from snaps
                    // If labels are same, it means those are same snaps
                    // If not, it means update happened between two snaps
                    if (oldCopy[i].getLabel() != newCopy[i].getLabel()) {
                        // If update happened,
                        if (moved[i])
                            // Check if snap was moved or not
                            // If moved is true, it means update with clean snap 
                            // happened between two snaps by other threads
                            // Therefore just get it's clean snap
                            return oldCopy[i].getSnap();
                        else {
                            // If moved is false, it means i'th thread doesn't have clean snap
                            // Then set moved and flag to true, delete old snap and collect again
                            moved[i] = true;
                            flag = true;
                            delete[] oldCopy;
                            oldCopy = newCopy;
                            break;
                        }
                    }
                }

                // Flag with true means another collect is needed,
                // So skip return phase and go back to loop to collect again
                if (flag)
                    continue;

                // When getting clean snap succeed,
                // make new snap for update()
                std::valarray<T> ret = std::valarray<T>(size);
                for (size_t i = 0; i < size; ++i)
                    ret[i] = newCopy[i].getValue();
                return ret;
            }
        }

    private:
        SnapValue<T>* snapShots;
        size_t size;

        // Take snapshot at current state
        // Copy all snap value and return
        SnapValue<T>* collect() {
            SnapValue<T>* copy = new SnapValue<T>[size];
            for (size_t i = 0; i < size; ++i)
                copy[i] = snapShots[i];
            return copy;
        }

};