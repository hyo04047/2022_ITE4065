add_test( BwtreeInitTest.HandlesInitialization /root/CP/2022_ite4065_2016025041/project3/project3/release/bin/bwtree_test [==[--gtest_filter=BwtreeInitTest.HandlesInitialization]==] --gtest_also_run_disabled_tests)
set_tests_properties( BwtreeInitTest.HandlesInitialization PROPERTIES WORKING_DIRECTORY /root/CP/2022_ite4065_2016025041/project3/project3/release/test)
add_test( BwtreeTest.ConcurrentRandomInsert /root/CP/2022_ite4065_2016025041/project3/project3/release/bin/bwtree_test [==[--gtest_filter=BwtreeTest.ConcurrentRandomInsert]==] --gtest_also_run_disabled_tests)
set_tests_properties( BwtreeTest.ConcurrentRandomInsert PROPERTIES WORKING_DIRECTORY /root/CP/2022_ite4065_2016025041/project3/project3/release/test)
add_test( BwtreeTest.ConcurrentMixed /root/CP/2022_ite4065_2016025041/project3/project3/release/bin/bwtree_test [==[--gtest_filter=BwtreeTest.ConcurrentMixed]==] --gtest_also_run_disabled_tests)
set_tests_properties( BwtreeTest.ConcurrentMixed PROPERTIES WORKING_DIRECTORY /root/CP/2022_ite4065_2016025041/project3/project3/release/test)
add_test( BwtreeTest.ConcurrentSkewedInsert /root/CP/2022_ite4065_2016025041/project3/project3/release/bin/bwtree_test [==[--gtest_filter=BwtreeTest.ConcurrentSkewedInsert]==] --gtest_also_run_disabled_tests)
set_tests_properties( BwtreeTest.ConcurrentSkewedInsert PROPERTIES WORKING_DIRECTORY /root/CP/2022_ite4065_2016025041/project3/project3/release/test)
set( bwtree_test_TESTS BwtreeInitTest.HandlesInitialization BwtreeTest.ConcurrentRandomInsert BwtreeTest.ConcurrentMixed BwtreeTest.ConcurrentSkewedInsert)
