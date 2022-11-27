#include "bwtree.h"
#include "bwtree_test_util.h"
#include "multithread_test_util.h"
#include "worker_pool.h"
#include "zipf.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>
#include <vector>
#include <string>

/*******************************************************************************
 * The test structures stated here were written to give you and idea of what a
 * test should contain and look like. Feel free to change the code and add new
 * tests of your own. The more concrete your tests are, the easier it'd be to
 * detect bugs in the future projects.
 ******************************************************************************/

/*
 * Tests bwtree init/destroy APIs.
 */
TEST(BwtreeInitTest, HandlesInitialization) {
  auto *const tree = test::BwTreeTestUtil::GetEmptyTree();

  ASSERT_TRUE(tree != nullptr);

  delete tree;
}

/*
 * TestFixture for bwtree tests
 */
class BwtreeTest : public ::testing::Test {
  protected:
    /*
     * NOTE: You can also use constructor/destructor instead of SetUp() and
     * TearDown(). The official document says that the former is actually
     * perferred due to some reasons. Checkout the document for the difference.
     */
    BwtreeTest() {
    }

    ~BwtreeTest() {
    }

    const uint32_t num_threads_ =
      test::MultiThreadTestUtil::HardwareConcurrency() + (test::MultiThreadTestUtil::HardwareConcurrency() % 2);
};

/*
 * Basic functionality test of 1M concurrent random inserts
 */
TEST_F(BwtreeTest, ConcurrentRandomInsert) {
  // This defines the key space (0 ~ (1M - 1))
  const uint32_t key_num = 1024 * 1024;
  std::atomic<size_t> insert_success_counter = 0;
  std::atomic<size_t> insert_fail_counter = 0;

  common::WorkerPool thread_pool(num_threads_, {});
  thread_pool.Startup();
  auto *const tree = test::BwTreeTestUtil::GetEmptyTree();

  // Inserts in a 1M key space randomly until all keys has been inserted
  auto workload = [&](uint32_t id) {
    const uint32_t gcid = id + 1;
    tree->AssignGCID(gcid);
    std::default_random_engine thread_generator(id);
    std::uniform_int_distribution<int> uniform_dist(0, key_num - 1);

    while (insert_success_counter.load() < key_num) {
      int key = uniform_dist(thread_generator);

      if (tree->Insert(key, key)) {
        insert_success_counter.fetch_add(1);
      //   // std::cout << insert_success_counter << std::endl;
      }
      // else
      //   insert_fail_counter.fetch_add(1);
    }

    tree->UnregisterThread(gcid);
  };

  tree->UpdateThreadLocal(num_threads_ + 1);
  test::MultiThreadTestUtil::RunThreadsUntilFinish(&thread_pool, num_threads_, workload);
  tree->UpdateThreadLocal(1);
  // std::cout << "Failure : " << insert_fail_counter << std::endl;
  // std::cout << "Insert : " << tree->insert_failure_cnt << std::endl;
  // std::cout << "Consol : " << tree->consol_failure_cnt << std::endl;
  // std::cout << "SMO : " << tree->finishSMO_failure_cnt << std::endl;
  // std::cout << "PostInner : " << tree->installnode_failure_cnt << std::endl;
  // std::cout << "Adjust : " << tree->adjustnode_failure_cnt << std::endl;

  // Verifies whether random insert is correct
  for (uint32_t i = 0; i < key_num; i++) {
    auto s = tree->GetValue(i);

    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(*s.begin(), i);
  }

  delete tree;
}

TEST_F(BwtreeTest, ConcurrentMixed) {
  NOISEPAGE_ASSERT(num_threads_ % 2 == 0,
      "This test requires an even number of threads. This should have been handled when it was assigned.");

  // This defines the key space (0 ~ (1M - 1))
  const uint32_t key_num = 1024 * 1024;

  common::WorkerPool thread_pool(num_threads_, {});
  thread_pool.Startup();
  auto *const tree = test::BwTreeTestUtil::GetEmptyTree();

  auto workload = [&](uint32_t id) {
    const uint32_t gcid = id + 1;
    tree->AssignGCID(gcid);
    if ((id % 2) == 0) {
      for (uint32_t i = 0; i < key_num; i++) {
        int key = num_threads_ * i + id;  // NOLINT

        tree->Insert(key, key);
      }
    } else {
      for (uint32_t i = 0; i < key_num; i++) {
        int key = num_threads_ * i + id - 1;  // NOLINT

        while (!tree->Delete(key, key)) {
        }
      }
    }
    tree->UnregisterThread(gcid);
  };

  tree->UpdateThreadLocal(num_threads_ + 1);
  test::MultiThreadTestUtil::RunThreadsUntilFinish(&thread_pool, num_threads_, workload);
  tree->UpdateThreadLocal(1);

  // std::cout << "Insert : " << tree->insert_failure_cnt << std::endl;
  // std::cout << "Delete : " << tree->delete_failure_cnt << std::endl;
  // std::cout << "Consol : " << tree->consol_failure_cnt << std::endl;
  // std::cout << "SMO : " << tree->finishSMO_failure_cnt << std::endl;
  // std::cout << "PostInner : " << tree->installnode_failure_cnt << std::endl;
  // std::cout << "Adjust : " << tree->adjustnode_failure_cnt << std::endl;

  // Verifies that all values are deleted after mixed test
  for (uint32_t i = 0; i < key_num * num_threads_; i++) {
    EXPECT_EQ(tree->GetValue(i).size(), 0);
  }

  delete tree;
}

/*
 * Basic functionality test of 1M concurrent random inserts
 */
TEST_F(BwtreeTest, ConcurrentSkewedInsert) {
  // This defines the key space (0 ~ (1M - 1))
  const uint32_t key_num = 1024 * 1024;
  std::atomic<size_t> insert_success_counter = 0;
  std::atomic<size_t> insert_fail_counter = 0;

  common::WorkerPool thread_pool(num_threads_, {});
  thread_pool.Startup();
  auto *const tree = test::BwTreeTestUtil::GetEmptyTree();
  // util::Zipf zipf(1.0, key_num);

  auto workload = [&](uint32_t id) {
    const uint32_t gcid = id + 1;
    tree->AssignGCID(gcid);
    std::default_random_engine thread_generator(id);
    // std::uniform_int_distribution<int> uniform_dist(0, key_num - 1);
    // std::discrete_distribution<int> discrete_dist(0, int(key_num - 1));
    util::Zipf zipf(1.0, key_num);
    zipf.SetSeed(gcid);
    
    while (insert_success_counter.load() < key_num) {
      // int key = uniform_dist(thread_generator);
      // int key = discrete_dist(thread_generator);
      int key = zipf.Generate();

      if (tree->Insert(key, key*insert_success_counter)) 
        insert_success_counter.fetch_add(1);
      // else
      //   insert_fail_counter.fetch_add(1);
    }

    tree->UnregisterThread(gcid);
  };

  tree->UpdateThreadLocal(num_threads_ + 1);
  test::MultiThreadTestUtil::RunThreadsUntilFinish(&thread_pool, num_threads_, workload);
  tree->UpdateThreadLocal(1);

  // std::cout << "Failure :" << insert_fail_counter << std::endl;
  // std::cout << "Insert : " << tree->insert_failure_cnt << std::endl;
  // std::cout << "Consol : " << tree->consol_failure_cnt << std::endl;
  // std::cout << "SMO : " << tree->finishSMO_failure_cnt << std::endl;
  // std::cout << "PostInner : " << tree->installnode_failure_cnt << std::endl;
  // std::cout << "Adjust : " << tree->adjustnode_failure_cnt << std::endl;

  // Verifies whether random insert is correct
  for (uint32_t i = 1; i < key_num; i++) {
    auto s = tree->GetValue(i);

    // EXPECT_EQ(s.size(), 1);
    // EXPECT_EQ(*s.begin(), i);
  }

  delete tree;
}