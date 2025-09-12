import pygame
import sys
import time
import os

# Inicializace PyGame
pygame.init()

# Konstanty
WIDTH, HEIGHT = 800, 600
FPS = 30
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BG_COLOR = (180, 220, 255)

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Tamagotchi Drak')
font = pygame.font.SysFont(None, 32)
clock = pygame.time.Clock()

# Načtení obrázku mazlíčka (zatím placeholder)
ASSET_PATH = os.path.join('assets', 'dragon.png')
if os.path.exists(ASSET_PATH):
    dragon_img = pygame.image.load(ASSET_PATH)
    dragon_img = pygame.transform.scale(dragon_img, (200, 200))
else:
    dragon_img = pygame.Surface((200, 200), pygame.SRCALPHA)
    pygame.draw.ellipse(dragon_img, (0, 200, 0), (0, 40, 200, 120))
    pygame.draw.circle(dragon_img, (0, 200, 0), (150, 80), 40)
    pygame.draw.circle(dragon_img, (0, 0, 0), (170, 80), 8)
    pygame.draw.polygon(dragon_img, (200, 200, 0), [(160, 50), (170, 20), (180, 50)])

# Stav mazlíčka
dragon = {
    'hunger': 100,
    'happiness': 100,
    'energy': 100,
}

def draw_bar(x, y, value, color, label):
    pygame.draw.rect(screen, BLACK, (x-2, y-2, 204, 24), 2)
    pygame.draw.rect(screen, color, (x, y, 2*value, 20))
    text = font.render(label, True, BLACK)
    screen.blit(text, (x, y-28))

# Definice tlačítek
class Button:
    def __init__(self, x, y, w, h, color, text, action):
        self.rect = pygame.Rect(x, y, w, h)
        self.color = color
        self.text = text
        self.action = action
    def draw(self, surface):
        pygame.draw.rect(surface, self.color, self.rect)
        pygame.draw.rect(surface, BLACK, self.rect, 2)
        txt = font.render(self.text, True, BLACK)
        surface.blit(txt, (self.rect.x + 10, self.rect.y + 10))
    def is_clicked(self, pos):
        return self.rect.collidepoint(pos)

# Vytvoření tlačítek
buttons = [
    Button(350, 450, 120, 40, (255, 200, 200), 'Nakrmit', lambda: dragon.update({'hunger': min(100, dragon['hunger'] + 20)})),
    Button(500, 450, 120, 40, (200, 255, 200), 'Hrát si', lambda: dragon.update({'happiness': min(100, dragon['happiness'] + 20)})),
    Button(650, 450, 120, 40, (200, 200, 255), 'Spánek', lambda: dragon.update({'energy': min(100, dragon['energy'] + 20)})),
]

# Hlavní smyčka
running = True
last_update = pygame.time.get_ticks()
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            for btn in buttons:
                if btn.is_clicked(event.pos):
                    btn.action()

    now = pygame.time.get_ticks()
    if now - last_update > 1000:
        dragon['hunger'] = max(0, dragon['hunger'] - 1)
        dragon['happiness'] = max(0, dragon['happiness'] - 1)
        dragon['energy'] = max(0, dragon['energy'] - 1)
        last_update = now

    if dragon['hunger'] == 0 or dragon['happiness'] == 0 or dragon['energy'] == 0:
        screen.fill((100, 0, 0))
        over_text = font.render('GAME OVER! Stiskni R pro restart.', True, WHITE)
        screen.blit(over_text, (WIDTH//2-200, HEIGHT//2))
        pygame.display.flip()
        keys = pygame.key.get_pressed()
        if keys[pygame.K_r]:
            dragon = {'hunger': 100, 'happiness': 100, 'energy': 100}
        continue

    screen.fill(BG_COLOR)
    screen.blit(dragon_img, (WIDTH//2-100, HEIGHT//2-150))
    draw_bar(100, 450, dragon['hunger'], (200, 0, 0), 'Hlad')
    draw_bar(100, 500, dragon['happiness'], (0, 200, 0), 'Štěstí')
    draw_bar(100, 550, dragon['energy'], (0, 0, 200), 'Energie')
    help_text = font.render('F = nakrmit, H = hrát si, E = spánek', True, BLACK)
    screen.blit(help_text, (WIDTH//2-180, 30))
    for btn in buttons:
        btn.draw(screen)
    pygame.display.flip()
    clock.tick(FPS)

pygame.quit()
sys.exit()
