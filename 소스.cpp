#include <SDL.h>
#include <iostream>

// ��ü�� ��ġ�� �ӵ��� ��Ÿ���� ����ü
struct Object {
    float x, y;     // ��ġ
    float vx, vy;   // �ӵ�

    Object(float x, float y) : x(x), y(y), vx(0.0f), vy(0.0f) {}//������
};

// ȭ�� ũ��
const int screen_x = 800, screen_y = 600;

//���� ������
const int radius = 10;

// ���� �ʱ� ��ġ
const float start_x = screen_x / 2, start_y = screen_y - 30;

// �߷� ���ӵ�
const float gravity = 0.098f;

// ���� �ʱ� �ӵ�
const float jump_speed = -3.5f;

int main(int argc, char* argv[]) {

    // SDL ������ ����
    SDL_Window* window = SDL_CreateWindow("gravity", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_x, screen_y, SDL_WINDOW_SHOWN);

    // SDL ������ ����
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // ��ü ����
    Object obj(start_x, start_y);

    // �̺�Ʈ ó�� ����
    bool g_flag_running = false;
    bool jumping = false;
    while (!g_flag_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                g_flag_running = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE && !jumping) {
                    obj.vy = jump_speed;
                    jumping = true;
                }
                else if (event.key.keysym.sym == SDLK_LEFT) {
                    obj.vx = -1.0f;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                   obj.vx = 1.0f;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
                    obj.vx = 0.0f;
                }
            }
        }

        // �߷� ����
        obj.vy += gravity;

        // ��ü �̵�
        if (obj.vx < 0 and obj.x > 10) {
            obj.x += obj.vx;
        }
        else if (obj.vx > 0 and obj.x < screen_x - 10) {
            obj.x += obj.vx;
        }
        obj.y += obj.vy;
        
        // ��ü�� ���鿡 �����ϸ� ���� ���� ����
        if (obj.y >= start_y) {
            obj.y = start_y;
            obj.vy = 0.0f;
            jumping = false;
        }

        // ȭ�� �����
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // �� �׸���
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect groundRect = { 0, screen_y - 20, screen_x, 20 };
        SDL_RenderFillRect(renderer, &groundRect);

        // �� �׸���
        SDL_SetRenderDrawColor(renderer, 50, 150, 10, 255);
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (dx * dx + dy * dy <= radius * radius) {
                    SDL_RenderDrawPoint(renderer, static_cast<int>(obj.x) + dx, static_cast<int>(obj.y) + dy);
                }
            }
        }


        // ȭ�� ������Ʈ
        SDL_RenderPresent(renderer);

        // ª�� ���� �ð� �߰�
        SDL_Delay(10);
    }

    // SDL ����
    SDL_DestroyRenderer;
    return 0;
}