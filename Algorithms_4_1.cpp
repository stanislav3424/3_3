#include <iostream>

class DynamicArray
{
private:
    int* data = nullptr;
    int actualSize = 0;
    int logicalSize = 0;
    int resizeRange = 0;

public:
    DynamicArray(int resizeRange = 5) : resizeRange{(resizeRange < 1) ? 1 : resizeRange}
    {
        checkActualSize();
    }

    DynamicArray(const DynamicArray& targetArr)
        : actualSize{targetArr.actualSize}, logicalSize{targetArr.logicalSize}, resizeRange{targetArr.resizeRange}
    {
        data = new int[actualSize];
        for (int index = 0; index < logicalSize; ++index)
            data[index] = targetArr.data[index];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void resize(int newSize)
    {
        if (newSize < 0)
            newSize = 0;

        int oldLogicalSize = logicalSize;
        logicalSize = newSize;
        checkActualSize(oldLogicalSize);

        if (logicalSize > oldLogicalSize)
        {
            for (int i = oldLogicalSize; i < logicalSize; ++i)
            {
                data[i] = 0;
            }
        }
    }

    void add(int value)
    {
        if (logicalSize >= actualSize)
        {
            checkActualSize();
        }
        data[logicalSize] = value;
        ++logicalSize;
        checkActualSize();
    }

    void set(int index, int value, bool resizeArr = false)
    {
        if (index < 0)
            return;

        if (index >= logicalSize)
        {
            if (resizeArr)
            {
                resize(index + 1);
            }
            else
            {
                return;
            }
        }
        data[index] = value;
    }

    void remove(int index)
    {
        if (!isValidIndex(index))
            return;
        for (int i = index; i < logicalSize - 1; ++i)
        {
            data[i] = data[i + 1];
        }
        --logicalSize;
        checkActualSize();
    }

    void removeLast()
    {
        if (logicalSize > 0)
        {
        --logicalSize;
        }
        checkActualSize();
    }

    bool isValidIndex(int index) const
    {
        return (index >= 0) && (index < logicalSize);
    }

    bool isLastElement(int index) const
    {
        return index + 1 == logicalSize;
    }

    int& operator[](int index)
    {
        if (!isValidIndex(index))
        {
            throw std::out_of_range("out_of_range");
        }
        return data[index];
    }

    const int& operator[](int index) const
    {
        if (!isValidIndex(index))
        {
            throw std::out_of_range("out_of_range");
        }
        return data[index];
    }

    DynamicArray& operator=(const DynamicArray& Data)
    {
        delete[] data;
        logicalSize = Data.logicalSize;
        actualSize = Data.actualSize;
        resizeRange = Data.resizeRange;

        data = new int[actualSize];
        for (int index = 0; index < logicalSize; ++index)
            data[index] = Data.data[index];
        return *this;
    }

    int getActualSize() const
    {
        return actualSize;
    }

    int getSize() const
    {
        return logicalSize;
    }

private:
    void checkActualSize(int oldLogicalSize = -1)
    {
        if (oldLogicalSize == -1)
        {
            oldLogicalSize = logicalSize;
        }

        if (actualSize == 0)
        {
            actualSize = resizeRange;
            newData();
            return;
        }

        if (logicalSize >= actualSize)
        {
            while (actualSize <= logicalSize)
            {
                actualSize += resizeRange;
            }
            newData(oldLogicalSize);
            return;
        }

        if (actualSize - logicalSize > resizeRange * 2)
        {
            while (actualSize - logicalSize > resizeRange)
            {
                actualSize -= resizeRange;
            }
            newData(oldLogicalSize);
            return;
        }
    }

    void newData(int oldLogicalSize = -1)
    {
        int* newDataArray = new int[actualSize]();

        if (oldLogicalSize == -1)
        {
            oldLogicalSize = logicalSize;
        }
        else
        {
            oldLogicalSize = std::min(oldLogicalSize, logicalSize);
        }

        if (data)
        {
            for (int i = 0; i < oldLogicalSize; ++i)
            {
                newDataArray[i] = data[i];
            }
            delete[] data;
        }

        data = newDataArray;
    }
};

int main()
{
        DynamicArray arr1;
        DynamicArray arr2;
        arr1.add(5);
        arr1.add(9);
        arr1.add(6);
        arr2.add(2);
        arr2.add(1);
        arr2.add(12);
        arr2.add(6);

        arr1 = arr2;

        for (int index = 0; index < arr1.getSize(); ++index)
            std::cout << arr1[index] << std::endl;

        return 0;
}