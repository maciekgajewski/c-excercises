#include "headers/catch/catch.h"

#include "linked-list.h"

#include <vector>
#include <string>

template<typename T>
bool ContentMatches(const LinkedList<T>& list, const std::vector<T>& expected)
{
    if(list.size() != expected.size())
    {
        WARN ("Lengths differ " << list.size() << " != " << expected.size() );
        return false;
    }
    
    auto listCurrent = list.begin();
    const auto lend = list.end();
    auto expectedCurrent = expected.begin();    
    
    for(int index = 1; listCurrent != lend; ++listCurrent, ++expectedCurrent, ++index)
    {
        if(*listCurrent != *expectedCurrent)
        {
            WARN ("Element " << index << " not equal " << *listCurrent << " != " << *expectedCurrent );
            return false;
        }
    }
    
    return true;
}

SCENARIO("Lists maintain their size") {
    
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

SCENARIO("Lists are iteratable") {
    
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
        list.push_front(13);
        list.push_front(11);
        list.push_front(9);
        list.push_front(7);
        list.push_front(3);
               
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

SCENARIO("Iterators are erasable") {
    
     GIVEN("a list of 3 items") {
        LinkedList<int> list;    
        list.push_front(3);
        list.push_front(7);
        list.push_front(9);
               
        WHEN("the second item is erased") {
            auto iter = list.begin();
            ++iter;
            list.erase(iter);
            
            THEN("only two items remain"){
                REQUIRE( list.size() == 2 );
            }      
              
            AND_WHEN("the second item is erased again") {
                auto iter = list.begin();
                ++iter;
                list.erase(iter);
                
                THEN("only one items remain"){
                    REQUIRE( list.size() == 1 );
                }    
                
                AND_WHEN("the last item is erased") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
        
        WHEN("the last item is erased") {
            auto iter = list.begin();
            ++iter;
            ++iter;
            list.erase(iter);
            
            THEN("only two items remain"){
                REQUIRE( list.size() == 2 );
            }      
              
            AND_WHEN("the last item is erased again") {
                auto iter = list.begin();
                ++iter;
                list.erase(iter);
                
                THEN("only one items remain"){
                    REQUIRE( list.size() == 1 );
                }    
                
                AND_WHEN("the last item is erased again") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
        
        WHEN("the end iterator is erased") {
            list.erase(list.end());
            
            THEN("nothing happens"){
                REQUIRE( list.size() == 3 );
            }  
        }
        
        
        WHEN("the begin iterator is erased") {
            list.erase(list.begin());
            
            THEN("2 items remain"){
                REQUIRE( list.size() == 2 );
            }  
            
            AND_WHEN("the begin iterator is erased again") {
                list.erase(list.begin());
                
                THEN("only one items remain"){
                    REQUIRE( list.size() == 1 );
                }    
                
                AND_WHEN("the begin iterator is erased again") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
     }
}

SCENARIO("Content of lists are maintained in the correct order when adding") {
             
     GIVEN("an empty list") {
        LinkedList<int> list;      
               
        WHEN("13, 11, 9, 7, 3 are pushed onto the front") {  
            list.push_front(13);
            list.push_front(11);
            list.push_front(9);
            list.push_front(7);
            list.push_front(3);
                
            THEN("the contents is 3, 7, 9, 11, 13 in order"){                
                REQUIRE( ContentMatches(list, std::vector<int>{{3, 7, 9, 11,  13}}) );
            }            
            
            AND_WHEN("15 is pushed") {
                list.push_front(15);                 
                    
                THEN("the contents is 15, 3, 7, 9, 11, 13 in order"){
                    REQUIRE( ContentMatches(list, std::vector<int>{{15, 3, 7, 9, 11,  13}}) );
                }     
            }
        }
     }
}

SCENARIO("Content of lists are maintained in the correct order when removing") {
     GIVEN("an list 13, 11, 9, 7, 3 ") {
        LinkedList<int> list;                     
        list.push_front(13);
        list.push_front(11);
        list.push_front(9);
        list.push_front(7);
        list.push_front(3);
        
        WHEN("an item is removed") {
                list.pop_front();               
                
            THEN("the contents is 7, 9, 11, 13 in order"){
                REQUIRE( ContentMatches(list, std::vector<int>{{7, 9, 11,  13}}) );
            }  
        
            AND_WHEN("another item is removed") {
                list.pop_front();               
                
                THEN("the contents is 9, 11, 13 in order"){
                    REQUIRE( ContentMatches(list, std::vector<int>{{9, 11,  13}}) );
                }  
            }
        }
        
        WHEN("all items are removed the list is empty") {
            list.pop_front();
            list.pop_front();
            list.pop_front();
            list.pop_front();
            list.pop_front();
                                                
            THEN("no iterations are performed"){
                REQUIRE( list.empty() == true );
            }
        }
    }
}

SCENARIO("Content of lists are maintained in the correct order when erasing") {        
    GIVEN("a list of 9, 7, 3") {
        LinkedList<int> list;    
        list.push_front(3);
        list.push_front(7);
        list.push_front(9);
               
        WHEN("the second item is erased") {
            auto iter = list.begin();
            ++iter;
            list.erase(iter);
            
            THEN("the list becomes 9, 3"){
                REQUIRE( ContentMatches(list, std::vector<int>{{9, 3}}) );
            }      
              
            AND_WHEN("the second item is erased again") {
                auto iter = list.begin();
                ++iter;
                list.erase(iter);
                
                THEN("the list becomes 9"){
                    REQUIRE( ContentMatches(list, std::vector<int>{{9}}) );
                }    
                
                AND_WHEN("the last item is erased") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
        
        WHEN("the last item is erased") {
            auto iter = list.begin();
            ++iter;
            ++iter;
            list.erase(iter);
            
            THEN("the list becomes 9, 7"){
                REQUIRE( ContentMatches(list, std::vector<int>{{9, 7}}) );
            }      
              
            AND_WHEN("the last item is erased again") {
                auto iter = list.begin();
                ++iter;
                list.erase(iter);
                
                THEN("the list becomes"){
                    REQUIRE( ContentMatches(list, std::vector<int>{{9}}) );
                }    
                
                AND_WHEN("the last item is erased again") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
        
        WHEN("the end iterator is erased") {
            list.erase(list.end());
            
            THEN("nothing happens"){
                REQUIRE( ContentMatches(list, std::vector<int>{{9, 7, 3 }}) );
            }  
        }
        
        
        WHEN("the begin iterator is erased") {
            list.erase(list.begin());
            
            THEN("the list becomes 7, 3"){
                REQUIRE( ContentMatches(list, std::vector<int>{{7, 3 }}) );
            }  
            
            AND_WHEN("the begin iterator is erased again") {
                list.erase(list.begin());
                
                THEN("the list becomes 3"){
                    REQUIRE( ContentMatches(list, std::vector<int>{{ 3 }}) );
                }    
                
                AND_WHEN("the begin iterator is erased again") {
                    list.erase(list.begin());
                    
                    THEN("the list is empty"){
                        REQUIRE( list.empty() );
                    }       
                }
            }
        }
     }
}

SCENARIO("It is possible to copy a list") {
    GIVEN("a list of doubles") {
        LinkedList<double> list;
        list.push_front(3.3);
        list.push_front(4.4);
        list.push_front(5.6);
        list.push_front(6.7);
        
        WHEN("creating a copy"){
            LinkedList<double> copy(list);
            
            THEN("keeps the values available in the original list") {
                REQUIRE( ContentMatches(list, std::vector<double>{{6.7, 5.6, 4.4, 3.3}}) );
                
                AND_THEN("the copied list also contains the values"){
                    REQUIRE( ContentMatches(copy, std::vector<double>{{6.7, 5.6, 4.4, 3.3}}) );
                }
            }
        }
        
        WHEN("creating a copy and removing an item from the copy") {
            LinkedList<double> copy = list;
            copy.pop_front();
            
            THEN("the original list is unmodified") {
                REQUIRE( ContentMatches(list, std::vector<double>{{6.7, 5.6, 4.4, 3.3}}) );
            
                AND_THEN("the copied list removes the front item"){
                    REQUIRE( ContentMatches(copy, std::vector<double>{{5.6, 4.4, 3.3}}) );
                }  
            }
        }
                
        WHEN("creating a copy and removing an item from the original") {
            LinkedList<double> copy = list;
            list.pop_front();
            
            THEN("the original list loses the front item") {
                REQUIRE( ContentMatches(list, std::vector<double>{{5.6, 4.4, 3.3}}) );
            
                AND_THEN("the copied list remains intact"){
                    REQUIRE( ContentMatches(copy, std::vector<double>{{6.7, 5.6, 4.4, 3.3}}) );
                }  
            }
        }
    }
}

SCENARIO("It is possible to access the data at the front of the list") {
    GIVEN("A list of two items") {
        LinkedList<std::string> list;
        list.push_front("World");
        list.push_front("Hello");
        
        WHEN("accessing the front item") {
            auto item = list.front();
            
            THEN("the value is the last added item") {
                REQUIRE( item== "Hello" );
            }
        }
        
        WHEN("removing an item from the list"){
            list.pop_front();
            THEN("the first item is the next item") {
                REQUIRE(list.front() == "World");
            }
        }
        
        // TODO: What about calling front() on an empty list??
    }
}

SCENARIO("It is possible to modify the data at the front of the list") {
	GIVEN("A list of two items") {
		LinkedList<double> list;
		list.push_front(1.12);
		list.push_front(3.14);

		WHEN("accessing the front item") {
			double& item = list.front();
			item = 6.2;

			THEN("the first item in the list is modified") {
				REQUIRE(list.front() == 6.2);
			}
		}
	}
}
