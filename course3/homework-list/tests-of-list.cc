#include "headers/catch/catch.h"

#include "linked-list.h"

SCENARIO("Lists maintain their size", "[list]") {
    
    GIVEN("an empty list") {
        LinkedList<int> list;
        
        REQUIRE( list.empty() == true );
        REQUIRE( list.size() == 0 );
        
        WHEN("an item is pushed") {
            list.push_front(3);
            
            THEN("the capacity increases by 1 and it is no longer empty"){
                REQUIRE( list.size() == 1 );
                REQUIRE( list.empty() == false );
            }       
        
            AND_WHEN("a second item is pushed") {
                list.push_front(7);
                
                THEN("the capacity increases by 1 more"){
                    REQUIRE( list.size() == 2 );
                    REQUIRE( list.empty() == false );
                }
                
                AND_WHEN("the second item is removed") {
                    list.pop_front();
                
                    THEN("the capacity decreases by 1"){
                        REQUIRE( list.size() == 1 );
                        REQUIRE( list.empty() == false );
                    }
                    
                    AND_WHEN("the first item is removed") {
                        list.pop_front();
                        
                        THEN("the capacity returns to empty"){
                            REQUIRE( list.size() == 0 );
                            REQUIRE( list.empty() == true );
                        }
                    }
                }  
            }         
        }
    }
}

SCENARIO("Lists are iteratable", "[list]") {
    
     GIVEN("an empty list") {
        LinkedList<int> list;
               
        WHEN("it is iterated over") {
            
            int count= 0;
            for(auto element : list)
                count++;
            
            THEN("no iterations are performed"){
                REQUIRE( count == 0 );
            }       
        }
     }
          
     GIVEN("a list of 5 items") {
        LinkedList<int> list;        
        list.push_front(3);
        list.push_front(7);
        list.push_front(9);
        list.push_front(11);
        list.push_front(13);
               
        WHEN("it is iterated over") {
            
            int count= 0;
            for(auto element : list)
                count++;
            
            THEN("5 iterations are performed"){
                REQUIRE( count == 5 );
            }
            
            AND_WHEN("an item is added before iteration") {
                    list.push_front(15);
                                        
                    int count= 0;
                    for(auto element : list)
                        count++;
                
                    THEN("6 iterations are performed"){
                        REQUIRE( count == 6 );
                    }
            }
            
            AND_WHEN("an item is removed before iteration") {
                    list.pop_front();
                                        
                    int count= 0;
                    for(auto element : list)
                        count++;
                
                    THEN("4 iterations are performed"){
                        REQUIRE( count == 4 );
                    }
            }
            
            AND_WHEN("all items are removed before iteration") {
                    list.pop_front();
                    list.pop_front();
                    list.pop_front();
                    list.pop_front();
                    list.pop_front();
                                        
                    int count= 0;
                    for(auto element : list)
                        count++;
                
                    THEN("no iterations are performed"){
                        REQUIRE( count == 0 );
                    }
            }
        }
     }
}
