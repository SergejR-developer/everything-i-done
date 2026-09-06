import requests
import matplotlib.pyplot as plt
import seaborn as sns
import json

def get_winrate(save = False):
    url = "https://api.opendota.com/api/heroStats"
    response = requests.get(url)

    if response.status_code == 200:
        data = response.json()

        hero_name = []
        hero_winrate = []

        for hero in data:
            hero_name.append(hero['name'])
            hero_winrate.append(hero['pub_win'] / hero['pub_pick'])

        heroes = dict(zip(hero_name, hero_winrate))

        if save:
            with open('dota.json', 'w') as file:
                json.dump(data, file)

        return heroes
    
    else:
        return None

data = get_winrate() #save=True

sns.histplot(data=data, x=data.values(), bins=20, kde=True)
plt.axvline(0.5, c = 'r')
plt.show()