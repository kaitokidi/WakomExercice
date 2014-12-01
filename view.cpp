#include <string>
#include <sstream>   
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){
    
    //VARIABLES CONSTANTS i ENUMERATIONS
    int speed = 180;
    float pantalla = 1;
    float time_to_next_sprite = 0.09;
    enum direction { down, left, right, up , none};
    const int mx[5] = {0,   -1,   1,    0,      0};
    const int my[5] = {1,    0,   0,   -1,      0};
    
    //VECTOR2
    sf::Vector2u size(1100,700);
    sf::Vector2f spriteSize(32,48);
    sf::Vector2i spriteSource(0,down);
    sf::Vector2f originalSpriteSize(0,0);
    sf::Vector2u newsize(size.x, size.y);
    sf::Vector2f oldMousePosition(sf::Vector2f(0,0));
    sf::Vector2f playerPosition(spriteSize.x,spriteSize.y);
    //OBJECTES DE SFML
        //DECLAREM LA VIEW
    sf::View view;
    sf::Image image;
    sf::Event event;
    sf::Clock deltaClock;
    sf::Sprite player, background;
    sf::Texture pTexture, tbackground;
    
    //LOAD THE IMAGES AND TEXTURES
    if(!image.loadFromFile("ground.png")) std::cout << "ground Image Not Loaded " << std::endl;
    if(!tbackground.loadFromImage(image)) std::cout << "background texture Not Loaded " << std::endl;
    if(!pTexture.loadFromFile("sprites.png")) std::cout << "personatge Not Loaded " << std::endl;
    spriteSize.x = originalSpriteSize.x = pTexture.getSize().x/4;
    spriteSize.y = originalSpriteSize.y = pTexture.getSize().y/4;

    
    //VARIABLES
    direction d = none;
    double escalat = 1;
    float distx = spriteSize.x/3, disty = spriteSize.y/4;
    float deltatime = 0, movx = 0.0, movy = 0.0, scont = 0.0;
    
    //Set player's properties
    player.setTexture(pTexture);
    player.setPosition(playerPosition);
    //Set Background's properties
    background.setTexture(tbackground);
    
    //CREATE THE WINDOW
    sf::RenderWindow window(/*sf::VideoMode(size.x,size.y)*/sf::VideoMode::getDesktopMode(), "Penguins <3", sf::Style::Resize|sf::Style::Close);

    //GAME LOOP
    while(window.isOpen()){
        speed = 180*((window.getSize().x - playerPosition.x)/window.getSize().x)+20;
        //Loop for handling events
        while(window.pollEvent(event)){
            switch (event.type){
                //Close event
                case sf::Event::Closed:
                    window.close();
                    break;
                    //KeyPressed event
                case sf::Event::KeyPressed:
                    //Close key
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                    //Default
                default:
                    //Do nothing
                    break;
            }
        }   
        
        //Deltatime
        deltatime = deltaClock.restart().asSeconds();
        scont += deltatime;
        
        //Updating if a key is pressed in a direction 'd'
        d = none;
	        if(sf::Mouse::getPosition().x > oldMousePosition.x) d = right;
		if(sf::Mouse::getPosition().x < oldMousePosition.x) d =  left;
	        if(sf::Mouse::getPosition().y > oldMousePosition.y) d =  down;
		if(sf::Mouse::getPosition().y < oldMousePosition.y) d =    up;
	oldMousePosition.x = sf::Mouse::getPosition().x;
	oldMousePosition.y = sf::Mouse::getPosition().y;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    d =    up;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  d =  down;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) d = right;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  d =  left;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::E))                                                                                                              sf::Mouse::setPosition(sf::Vector2i(window.getSize().x-3, playerPosition.y), window);
        
        //If some key is pressed
        if(d != none){
            //Set value to movement variables and update spritesource
            if(spriteSource.y == d){
//                movx += mx[d]*speed*deltatime;
//                movy += my[d]*speed*deltatime;
            }
            else spriteSource.y = d;
			if (scont >= time_to_next_sprite){
				scont = 0;
				++spriteSource.x;
			}
        }
        
        //Calcula el desti del player
        float destix = playerPosition.x;
		if(sf::Mouse::getPosition().x > playerPosition.x) destix += movx;
		if(sf::Mouse::getPosition().x < playerPosition.x) destix -= movx;
        float destiy = playerPosition.y+movy;
		destix = sf::Mouse::getPosition().x;
		destiy = sf::Mouse::getPosition().y-spriteSize.y/2;
    
        //Calcula l'equivalent del punt de la pantalla on esta el player en la imatge de background
		float px, py;
		if(destix > 0 && destiy > 0) {
			px = image.getSize().x*destix/tbackground.getSize().x/background.getScale().x;
			py = image.getSize().y*destiy/tbackground.getSize().y/background.getScale().y;
			
	       if(image.getPixel(px,py) != sf::Color::Black) {
				playerPosition.x = destix;
				playerPosition.y = destiy;
			}
			else {
				playerPosition.x = 1;
				playerPosition.y = 1;
				sf::Mouse::setPosition(sf::Vector2i(playerPosition.x, playerPosition.y), window);
			}
		}
		else {
			playerPosition.x = 1;
			playerPosition.y = 1;
			sf::Mouse::setPosition(sf::Vector2i(playerPosition.x, playerPosition.y), window);
		}
        
        //Setting movement variables to 0
        movx = movy = 0;
        
        //Checking the sprite sources and position to be ok
        if(spriteSource.x >= 4) spriteSource.x = 0;
        float aux = background.getTexture()->getSize().y * background.getScale().y;
        if(playerPosition.x < 0) playerPosition.x = 0;
        else if (playerPosition.x >= window.getSize().x-3) { 
			++pantalla;
			//if(!image.loadFromFile("ground2.png")) std::cout << "ground Image Not Loaded " << std::endl;
			//if(!tbackground.loadFromImage(image)) std::cout << "background texture Not Loaded " << std::endl;
			int t = pantalla + 1;
			std::stringstream d;
			d << "ground" <<  t;		
			std::string b = d.str();
			if(!image.loadFromFile(b+".png")) if(!pTexture.loadFromFile("sprites3.png")) { std::cout << "personatge Not Loaded " << std::endl; exit(1);}
			
			std::stringstream s;
			s << "ground" << pantalla;		
			std::string board = s.str();
			if(!image.loadFromFile(board+".png")) { std::cout << "I CAN'T LOAD BOARD IMAGE" << std::endl;     exit(1);}
			if(!tbackground.loadFromFile(board+".png")) { std::cout << "I CAN'T LOAD BOARD texture" << std::endl;   exit(1);}
			
			playerPosition.x = 5;
			playerPosition.y = 5;
			sf::Mouse::setPosition(sf::Vector2i(playerPosition.x, playerPosition.y), window);
		}
        else if (playerPosition.y < 0) playerPosition.y = 0;
        else if (playerPosition.y > aux) {
			playerPosition.x = 5;
			playerPosition.y = 5;
			sf::Mouse::setPosition(sf::Vector2i(playerPosition.x, playerPosition.y), window);
		}
        
        
        //Set player properties
        player.setOrigin(spriteSize.x/2, spriteSize.y);
        player.setPosition(playerPosition.x, playerPosition.y);
        player.setTextureRect(sf::IntRect(spriteSource.x*spriteSize.x,
                                        spriteSource.y*spriteSize.y, spriteSize.x, spriteSize.y));
       // player.setScale(window.getSize().x/600.0, window.getSize().x/600.0);
		player.setScale((window.getSize().x - playerPosition.x)/window.getSize().x , (window.getSize().x - playerPosition.x)/window.getSize().x);
        player.scale(originalSpriteSize.x/spriteSize.x, originalSpriteSize.y/spriteSize.y);
        
        //Set background scale
        escalat = (double)(window.getSize().x) / (double)(tbackground.getSize().x);
        background.setScale(escalat, escalat);
        
        //Set VIEW values
        view.reset(sf::FloatRect(playerPosition.x,playerPosition.y, window.getSize().x, window.getSize().y));
        //Definim on volem centrar la VIEW
        view.setCenter(playerPosition);
   
		sf::CircleShape c;
		c.setRadius(1);
		c.setOutlineThickness(2);
		c.setFillColor(sf::Color::Red);
		c.setPosition(playerPosition.x-0.5, playerPosition.y-0.5);
		
//         view.setRotation(playerPosition.y+playerPosition.x);
//         view.zoom((view.getSize().y/2) / playerPosition.y);
		view.zoom(0.4);
        //view.setViewport(sf::FloatRect(0,0,1,1));
        //Clear the window
        window.clear();
        //Set window view, draw and display
        window.draw(background);
        window.draw(player);
		window.draw(c);
//      window.setView(view);
        window.display();
    }
}
