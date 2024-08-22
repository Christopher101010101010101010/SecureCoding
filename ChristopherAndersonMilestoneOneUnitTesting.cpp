// Uncomment the next line to use precompiled headers
#include "pch.h"
#include <vector>

using namespace std;
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());

    int collectionSize = collection->size();
    add_entries(1);
    
    // is the collection still empty?
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), collectionSize + 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(10);                                        // initialize collection with 10 random integers

    int collectionSize = collection->size();                // initialize collectionSize to the current size of collection
    add_entries(5);                                         // add 5 new integers to collection

    ASSERT_EQ(collection->size(), collectionSize + 5);      // confirm that collection is now 5 objects larger than it's original state
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, GreaterThanOrEqualToSizes)
{
    add_entries(10);                                        // initialize collection with 10 random integers
    int currentCollectionSize = collection->size();         // initialize currentCollectionSize to size of collection

    ASSERT_GE(currentCollectionSize, 0);                    // test that currentCollection size is greater than 0, 1, 5, and 10 respectively
    ASSERT_GE(currentCollectionSize, 1);
    ASSERT_GE(currentCollectionSize, 5);
    ASSERT_GE(currentCollectionSize, 10);
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, GreaterThanOrEqualToCap)
{
    add_entries(10);                                        // initialize collection with 10 random integers
    int currCollectionCap = collection->capacity();         // initialize currCollectionCap to collection's capacity

    ASSERT_GE(currCollectionCap, 0);                        // test that currCollectionCap is greater than 0, 1, 5, and 10 respectively
    ASSERT_GE(currCollectionCap, 1);
    ASSERT_GE(currCollectionCap, 5);
    ASSERT_GE(currCollectionCap, 10);
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CollectionResizeInc)
{
    add_entries(10);                                        // initialize collection with 10 random integers
    int newCollectionSize = collection->size() + 13;        // initialize newCollectionSize to collection's size plus 13       
    
    collection->resize(newCollectionSize);                  // resize collection to the new collection size
    ASSERT_EQ(collection->size(), newCollectionSize);       // confirm that new collection size is equal to the original collection size plus 13
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CollectionResizeDecr)
{
    add_entries(10);                                        // initialize collection with 10 random integers

    int newCollectionSize = collection->size() - 2;         // initialize newCollectionSize to the collection size minus 2

    collection->resize(newCollectionSize);                  // resize collection to newCollectionSize
    ASSERT_EQ(collection->size(), newCollectionSize);       // confirm that the collection's new size is equal to newCollectionSize
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CollectionResizeDecrToZero)
{
    add_entries(10);                                        // initialize collection with 10 random integers

    collection->resize(0);                                  // resize collection to 0
    ASSERT_EQ(collection->size(), 0);                       // confirm that the collections current size is 0
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, CollectionVerifyFullErase)
{
    add_entries(10);                                        // initialize collection with 10 random integers

    collection->clear();                                    // clear the collection of all objects
    ASSERT_EQ(collection->size(), 0);                       // confirm that the collection's current size is 0
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CollectionEraseFunctionVerify)
{
    add_entries(10);                                                // initialize collection with 10 random integers

    collection->erase(collection->begin(), collection->end());      // erase all objects from the vector begin flag to the vector end flag
    ASSERT_EQ(collection->size(), 0);                               // confirm that the collection has been emptied
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CollectionReserveIncVerify)
{
    add_entries(10);                                                // initialize the collection with 10 random integers

    collection->reserve(collection->size() + 5);                    // increase the capacity of the collection by 5
    
    ASSERT_TRUE(collection->size() < collection->capacity());       // confirm that the size of the collection is less than the collection's capacity
    ASSERT_EQ(collection->capacity(), (collection->size() + 5));    // confirm that the capacity is equal to the size of the collection plus 5
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, CollectionOutOfRangeVerify)
{
    add_entries(10);                                                // initialize the collection with 10 random integers
    int collectionSize = collection->size();                        // initialize collectionSize with the collection's size
    int outOfRangeIndex = collectionSize + 25;                      // initialize outOfRange to the collectionSize plus 25

    ASSERT_THROW(collection->at(outOfRangeIndex), out_of_range);    // confirm that a call for data located at the outOfRange index of the collection 
                                                                    // will throw an out_of_range exception flag
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, ConfirmValueAdded)
{
    add_entries(10);                                                // initialize the collection with 10 random integers

    collection->push_back(102399);                                  // add integer constant 102399 to the back of the vector named collection
    int collectionLast = collection->size() - 1;                    // initialize collectionLast to the size of collection minus 1
    
    ASSERT_EQ(collection->at(collectionLast), 102399);              // confirm that the data at the collectionLast index of the collection vector is equal to 102399
}

TEST_F(CollectionTest, CollectionDataLossConfirmation) {
    add_entries(10);                                                // initialize the collection with 10 random integers

    collection->push_back(52345600000942);                          // attempt to add oversized integer constant 52345600000942 to vector of integers named collection
    ASSERT_FALSE(collection->at(10) == 52345600000942);             // confirm that new integer, 52345600000942, has not been properly storaged in collection
}





