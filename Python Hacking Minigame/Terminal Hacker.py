import random

def new_page():
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\
\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")

def intro():
    new_page()
    print("Welcome to the Terminal Hacking Game.\nType 'Play' to start the \
game, 'Help' to be given the rules, or 'Quit' to exit:")

def instructions():
    new_page()
    text_file = open("Game Instructions.txt", "r")
    instructions = text_file.read()
    print(instructions)
    text_file.close()
    helped = "string"
    while helped not in ("READY", "BACK"):
        helped = input("")
        helped = helped.upper()
        if helped == "READY":
            play_game()
        elif helped == "BACK":
            new_page()
            main()
        else:
            print("You didn't enter a correct input, try again.")
        
def user_quit():
    new_page()
    input("\nThank you for playing. Press Enter to exit.")


def play_game():
    #Creates list of available characters to use
    text_file = open("Characters.txt","r")
    characters = text_file.readlines()
    text_file.close()
    for i in range(len(characters)):
        changer = characters[i]
        characters[i] = changer[:1]

    #Creates a list of available words to use
    text_file = open("Words.txt","r")
    words = text_file.readlines()
    text_file.close()
    for i in range(len(words)):
        changer = words[i]
        words[i] = changer[:6]

    available_words = []
    def get_word():
        word=(words[random.randrange(len(words))])
        available_words.append(word)
        return word

    def new_log(line1,line2,line3):
        if log[0] != "":
            for i in range(14,-1,-1):
                log[i]=log[i-3]
            log[2] = ">" + line1
            log[1] = ">" + line2
            log[0] = ">" + line3
        elif log[0] == "":
            log[2] = ">" + line1
            log[1] = ">" + line2
            log[0] = ">" + line3
        return log[0],log[1],log[2],log[3],log[4],log[5],log[6],log[7],log[8],log[9],log[10],log[11],log[12],log[13],log[14]
        
    
    #Sets the value for a line for when it is made in the object
    def set_line():
        value = []
        for i in range(12):
            value.append(characters[random.randrange(len(characters))])
        chance = random.randrange(999)
        if chance < 375:
            word = get_word()
            words.remove(word)
            n = random.randrange(0,7)
            for i in range(0,6):
                value[n+i] = word [i]
        value = "".join(value)
        return value
    
    lines = []
    def make_lines():
        for i in range(32):
            lines.append(set_line())
    make_lines()

    incorrect_words = []
    correct_word = available_words[random.randrange(len(available_words))]
    for i in range(len(available_words)):
        if available_words[i] != correct_word:
            incorrect_words.append(available_words[i])
    
    def likeness(how):
        likeness = 0
        for i in range(6):
            if how[i] == correct_word[i]:
                likeness += 1
        likeness = str(likeness)
        likeness ="Likeness = " + likeness
        return likeness

    def clue(potential_clue):
        clue = 0
        length = len(potential_clue) - 1
        if (potential_clue[0] == "(") and (potential_clue[length] == ")"):
            clue = 1
        elif (potential_clue[0] == "{") and (potential_clue[length] == "}"):
            clue = 1
        elif (potential_clue[0] == "[") and (potential_clue[length] == "]"):
            clue = 1
        elif (potential_clue[0] == "<") and (potential_clue[length] == ">"):
            clue = 1
        for i in range(len(potential_clue)):
            if potential_clue[i] not in characters:
                clue = 0
        return clue

    def remove_dud():
        dud_line = ""
        dud = incorrect_words[random.randrange(len(incorrect_words))]
        if incorrect_words:
            incorrect_words.remove(dud)
        for i in range(32):
            if dud in lines[i]:
                lines[i]=lines[i].replace(dud,"."*len(dud))

    def remove_hint(the_clue):
        for i in range(32):
            if the_clue in lines[i]:
                lines[i]=lines[i].replace(the_clue,"."*len(the_clue))
                break
                                       
    log = ["","","","","","","","","","","","","","",""]
    win = 0
    guesses = 4
    attempts = ""

    def again(result):
        new_page()
        again = "string"
        if result == 1:
            print("Congratulations, you won and hacked the terminal successfully!\nYour streak is now",streak,".")
        elif result == 0:
            print("Unfortunately you ran out of attempts and were locked out of the terminal.\nYour streak has been reset to",streak,".")
        print("Enter 'Again' to play again, 'Menu' to return to the menu or 'Quit' to quit:")
        while again not in ("AGAIN","QUIT","MENU"):
            again = input("")
            again = again.upper()
            if again == "AGAIN":
                play_game()
            elif again == "MENU":
                main()
            elif again == "QUIT":
                user_quit()
            else:
                print ("You didn't enter a valid input, try again.")
        
    def show():
        if guesses != 1:
            attempts = "Attempts Remaining:"
        elif guesses == 1:
            attempts = "Attempt Remaining:"
        guesses_box = "■ " * guesses
        new_page()
        print("""
         Welcome to Terminal Hacking Minigame
         Password Required  
                                               
        """,guesses,"""""",attempts,"""""",guesses_box,"""           
                                               
         0x7BA0 """,(lines[0]),""" 0x7C60 """,(lines[16]),"""""",(log[14]),"""
         0x7BAC """,(lines[1]),""" 0x7C6C """,(lines[17]),"""""",(log[13]),"""
         0x7BB8 """,(lines[2]),""" 0x7C78 """,(lines[18]),"""""",(log[12]),"""
         0x7BC4 """,(lines[3]),""" 0x7C84 """,(lines[19]),"""""",(log[11]),"""
         0x7BD0 """,(lines[4]),""" 0x7C90 """,(lines[20]),"""""",(log[10]),"""
         0x7BDC """,(lines[5]),""" 0x7C9C """,(lines[21]),"""""",(log[9]),"""
         0x7BE8 """,(lines[6]),""" 0x7CA8 """,(lines[22]),"""""",(log[8]),"""
         0x7BF4 """,(lines[7]),""" 0x7CB4 """,(lines[23]),"""""",(log[7]),"""
         0x7C00 """,(lines[8]),""" 0x7CC0 """,(lines[24]),"""""",(log[6]),"""
         0x7C0C """,(lines[9]),""" 0x7CCC """,(lines[25]),"""""",(log[5]),"""
         0x7C18 """,(lines[10]),""" 0x7CD8 """,(lines[26]),"""""",(log[4]),"""
         0x7C24 """,(lines[11]),""" 0x7CE4 """,(lines[27]),"""""",(log[3]),"""
         0x7C30 """,(lines[12]),""" 0x7CF0 """,(lines[28]),"""""",(log[2]),"""
         0x7C3C """,(lines[13]),""" 0x7CFC """,(lines[29]),"""""",(log[1]),"""
         0x7C48 """,(lines[14]),""" 0x7D08 """,(lines[30]),"""""",(log[0]),"""
         0x7C54 """,(lines[15]),""" 0x7D14 """,(lines[31]),""" >""",end="")
        choice = input("")
        return choice

    
    while guesses != 0 and win == 0:
        choice = show()
        choice = choice.upper()
        in_there = 0
        for i in range(32):
            if choice in lines[i]:
                in_there += 1
            elif choice not in lines[i]:
                in_there += 0
        if in_there == 0 or choice == "":
            new_log("Error","Non-valid choice","Please try again")
        else:
            if choice == correct_word:
                new_log(choice,"Access granted","Press Enter")
                global streak
                streak += 1
                win += 1
            elif choice in available_words:
                new_log(choice,"Entry Denied.",likeness(choice))
                guesses -= 1
            elif clue(choice) == 0:
                new_log("Error","Non-valid choice","Please try again")
            elif clue(choice) == 1:
                clue_type = random.randrange(100)
                if clue_type < 24:
                    guesses = 4
                    remove_hint(choice)
                    new_log(choice,"Clue found:","Tries reset.")
                else:
                    remove_dud()
                    remove_hint(choice)
                    new_log(choice,"Clue found:","Dud removed.")
    if guesses == 0:
        log[1]= ">Init Lockout"
        log[0]= ">Press Enter"
        streak = 0
    show()
    again(win)
    
    
def main():
    from subprocess import call
    call('color a', shell=True)
    intro()
    menu = "string"
    while menu not in ("PLAY", "HELP", "QUIT"):
        menu = input("")
        menu = menu.upper()
        if menu == "PLAY":
            play_game()
        elif menu == "HELP":
            instructions()
        elif menu == "QUIT":
            user_quit()
        else:
            print("You didn't enter a valid input, try again.")
global streak
streak = 0
main()
