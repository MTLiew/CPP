#pragma once

#include <functional>
#include <vector>

template <typename TValue, typename TFunc = std::hash<TValue>>
class HashSet
{
private:
	// Unlike Java, the C++ hashtable array won't be Entry::FULL of null references.
	// It will be Entry::FULL of "Entry" objects, each of which tracks its current state
	// as Entry::EMPTY, Entry::FULL (with a value), or Entry::Entry::NIL (value was once here, but was removed).
	class Entry
	{
	public:
		enum EntryState { EMPTY, FULL, NIL};

		TValue value;
		EntryState state;

		Entry() : value(), state(Entry::EMPTY) {}
		Entry(const TValue& v) : value(v), state(Entry::EMPTY) {}
	};

	TFunc mHash;
	std::vector<Entry> mTable;
	std::size_t mCount;

public:
	// Constructs a hashtable with the given size, using the given function for
	// computing h(k).
	// hash must be a callable object (function, functor, etc.) that takes a parameter
	//    of type TValue and returns std::size_t (an integer).
	HashSet(int size)
	{
		for (int i = 0; true; i++)
		{
			if (size <= pow(2, i))
			{
				size = pow(2, i);
				break;
			}
		}

		mTable.resize(size);

		mCount = 0;

		for (int i = 0; i < size; i++)
		{
			mTable.at(i).state = Entry::EMPTY;
		}
	}

	// Inserts the given value into the set.
	void add(const TValue& value)
	{
		if (count() > loadFactor())
		{
			std::vector<Entry> nVector;
			nVector.resize(mTable.size() * 2);

			for (int i = 0; i < nVector.size(); i++)
			{
				nVector.at(i).state = Entry::EMPTY;
			}

			mTable.resize(mTable.size() * 2);

			for (int i = 0; i < mTable.size(); i++)
			{
				for (size_t j = 0; j < nVector.size(); j++)
				{
					size_t temp = (pow(j, 2) + j) / 2;

					size_t hashCode = (mHash(mTable.at(i).value) + temp) % nVector.size();

					if (nVector.at(hashCode).state == Entry::EMPTY)
					{
						nVector.at(hashCode).value = mTable.at(i).value;
						nVector.at(hashCode).state = mTable.at(i).state;
						break;
					}
				}
			}

			for (int i = 0; i < mTable.size(); i++)
			{
				mTable.at(i).state = Entry::EMPTY;
			}

			for (int i = 0; i < nVector.size(); i++)
			{
				if (nVector.at(i).state == Entry::FULL)
				{
					mTable.at(i).value = nVector.at(i).value;
					mTable.at(i).state = Entry::FULL;
				}

				if (nVector.at(i).state == Entry::NIL)
				{
					mTable.at(i).state = Entry::NIL;
				}
			}
		}

		if (find(value) == true);

		else
		{
			for (size_t i = 0; i < mTable.size(); i++)
			{
				size_t temp = (pow(i, 2) + i) / 2;

				size_t hashCode = (mHash(value) + temp) % mTable.size();

				if (mTable.at(hashCode).state == Entry::EMPTY)
				{
					mTable.at(hashCode).value = value;
					mTable.at(hashCode).state = Entry::FULL;
					mCount++;
					break;
				}
			}
		}
	}

	// Returns true if the given value is present in the set.
	bool find(const TValue& key)
	{
		for (size_t i = 0; i <= mTable.size(); i++)
		{
			size_t temp = (pow(i, 2) + i) / 2;

			size_t hashCode = (mHash(key) + temp) % mTable.size();

			if (mTable.at(hashCode).state == Entry::EMPTY)
				return false;

			else if (mTable.at(hashCode).state == Entry::FULL)
			{
				if (mTable.at(hashCode).value == key)
					return true;
			}
		}
		return false;
	}

	// Removes the given value from the set.
	void remove(const TValue& key)
	{	
		if (find(key) == true)
		{
			for (size_t i = 0; i < mTable.size(); i++)
			{
				size_t temp = (pow(i, 2) + i) / 2;

				size_t hashCode = (mHash(key) + temp) % mTable.size();

				if (mTable.at(hashCode).value == key)
				{
					mTable.at(hashCode).state = Entry::Entry::NIL;
					mCount--;
					break;
				}
			}
		}
	}

	int count()
	{
		return mCount;
	}

	double loadFactor()
	{
		return mTable.capacity() * 0.8;
	}
};