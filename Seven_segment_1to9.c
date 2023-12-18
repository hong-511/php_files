1.	The film primarily portrays the viewpoint of the Japanese soldiers defending the island. Viewing it from the American soldiers would present a different viewpoint, as the resistance of the defenders represents the greater effort required by the attackers to achieve their goals. The two sides have conflicting goals to achieve.
2.	War causes many family breakdowns and brutal sacrifices. Due to conscription, the protagonist is forced to separate from family, even never having met his child. At the end of the movie, everyone the protagonist knew is dead, both sides suffer heavy losses. This reminds me of a book I read before, "All Quiet on the Western Front. "Although the book describes the German battlefield during World War I, similarly conveys the brutality of war and its profound impact on an individual person. 
5.	The protagonist Saigo. A military officer is a simple character. He maintains a hostile stance towards the American throughout. However, Saigo is a complex character. After treating an injured American soldier, he gradually shifts from initially perceiving all Americans as enemies to realizing that American soldiers, like him, have families waiting for them to come back home. 
9.	Pacifism is the primary value depicted, mainly through portraying the brutality of war and its resulting casualties. For example, facing aerial bombing, the scene is filled with injured and deceased individuals with no time for reaction. Additionally, in war situations, Japanese soldiers choose to commit suicide rather than surrender, following orders from their superiors. In such unique wartime scenarios, the actions taken by people are worth careful reflection. Although the protagonist luckily survives in the end, it is challenging to ensure such fortune for everyone. For example, a soldier named Shimizu, who also desperately wanted to live, He decided to surrender alongside the protagonist, but after successfully surrendering, he was killed by American soldiers who considered bring prisoners will be targeted easily. The protagonist, who didn't succeed in surrendering, ironically survives until the end. The success or failure of one thing is difficult to determine from the beginning.
10. I prefer reading books because I believe that books and movies, as two mediums, differ in their ability to depict the intricacies of inner thoughts. Books can delicately describe a person's mental activities, detailing what they think, feel, and perceive in the moment. However, depicting such details in movies is more challenging, as understanding thoughts solely through visuals is difficult. On the other hand, the strength of movies lies in their ability to convey information through visuals. Compared to text, visual input is more straightforward, and the images and audio is move satisfying. But personally, I enjoy the portrayal of inner thoughts. I believe General Kuribayashi would be a highly Influenced figure because of he was educated in the United States, where he had many friends. However, as a Japanese military officer, he is tasked with representing his country to defend its territory. He has a deeper understanding of what the United States is like compared to those people around him, which adds complexity to his emotions toward the United States and his responsibilities. This conflict, I think, could be portrayed more clearly when using the medium of books.



#include <stdio.h>
#include <reg52.h>

#define LED7 P0
code unsigned char font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void delay(unsigned int i)
{
	unsigned int j, k;
	for(j = 0; j < i; j++)
		for (k = 0; k < 100; k++);
}

void main()
{
	unsigned int i = 0;
	while(1)
	{
		LED7 = font[i++];
		delay(500); 
		if (i == 10)
			i = 0;
	}
 }
