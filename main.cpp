#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

class  Question{
    private :
        size_t m_question{};
        std::string m_conv{};
        std::string m_input{};
        inline static size_t m_score{};
        
    public :

        Question(const size_t& radix, const size_t& range){
            random_gen(range);
            convert(radix);
            std::cout << "What is dec " << m_question << " in a system with radix " << radix << "? ";
            std::cin >> m_input;
            score();
        }

        void score(){
            if (m_conv == m_input){
                ++m_score;
                std::cout << "Correct!" << std::endl;
            } else {
                std::cout << "Wrong answer! " << m_question << " = " << m_conv << std::endl;
            }
        }

        static void print_score(const size_t& iterations){
            std::cout << "You scored : " << m_score << " / " << iterations << std::endl;
        }

        static void print_info(const Question& q){
            std::cout << std::right << std::setw(3) << q.m_question << " = " << std::left << std::setw(3) << q.m_conv << ". Your answer : " << q.m_input << std::endl; 
        }

        static void reset_score(){
            if (m_score != 0){
                m_score = 0;
            }
        }

        void random_gen(const size_t& range){
            m_question = static_cast<size_t>((std::rand() % range));
        }

        void convert(const size_t& radix){
            std::vector<int> a;
            size_t n {m_question};
            
            while (n > 0){
                size_t remainder {n % radix};
                n = n / radix;
                a.emplace(a.begin(), remainder);
            }

            //Padding with 0 if needed
            if (std::size(a) == 0){
                a.emplace(a.begin(), 0);
            }

            for (auto i{a.begin()}; i != a.end(); ++i){
                switch (*i){
                    case 10 :{
                        m_conv += 'A';
                    }
                    break;
                    case 11 :{
                        m_conv += 'B';
                    }
                    break;
                    case 12 :{
                        m_conv += 'C';
                    }
                    break;
                    case 13 :{
                        m_conv += 'D';
                    }
                    break;
                    case 14 :{
                        m_conv += 'E';
                    }
                    break;
                    case 15 :{
                        m_conv += 'F';
                    }
                    break;
                    default :{
                        m_conv += std::to_string(*i);
                    }
                    break;
                }
            }
        }
};

int main(){
    std::srand(std::time(0)); //Unique seed for the random number generator
    size_t range;
    size_t iterations;
    size_t radix;
    std::vector<Question> questions;
    bool end {false};

    while (end == false){
        std::cout << "Enter radix, max is 16 (e.g. '16' for hex, '8' for oct, '2' for bin etc...) : ";
        std::cin >> radix;
        std::cout << "Enter max dec range for the random number generator (e.g. '256' for two positions in hex) : "; 
        std::cin >> range;
        std::cout << "Enter the number of questions : ";
        std::cin >> iterations;

        //Delete leftovers before a new attempt
        if (std::size(questions) != 0){
            questions.clear();
        }
        
        //Reset score to '0' before a new attempt
        Question::reset_score();

        for (size_t i{}; i < iterations; ++i){
            std::cout << i + 1 << " : ";
            Question q(radix, range);
            questions.push_back(q);
        }
    
        std::cout << "-------------------------------" << std::endl;
    
        for (size_t i{}; i < iterations; ++i){
            std::cout << i + 1 << " : ";
            Question::print_info(questions[i]);
        }
    
        std::cout << "-------------------------------" << std::endl;

        Question::print_score(iterations);

        std::cout << "Try again? (y/n) : ";
        char go_on;
        std::cin >> go_on;
        end = ((go_on == 'Y') || (go_on == 'y')) ? false : true;
    }

    std::cout << "Goodbye!";
    return 0;
}