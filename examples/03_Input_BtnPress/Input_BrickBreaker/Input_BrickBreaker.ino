#include <M5StickCPlus2.h>

// Display size
int screenWidth = 0;
int screenHeight = 0;
LGFX_Sprite* sprite;

// Ball
struct Ball {
  int x, y;
  int size;
  int speedX, speedY;
  bool active;
};
Ball ball;

// Score
int score = 0;
bool gameOver = false;

void setup() {
  Serial.begin(115200);
  auto cfg = M5.config();
  StickCP2.begin(cfg);

  StickCP2.Display.setRotation(1);
  screenWidth = StickCP2.Display.width();    // 240
  screenHeight = StickCP2.Display.height();  // 135

  sprite = new LGFX_Sprite(&StickCP2.Display);
  sprite->setColorDepth(16);
  sprite->createSprite(screenWidth, screenHeight);
  sprite->pushSprite(0, 0);

  randomSeed(millis()); // for random ball direction
  resetGame();
}

// Paddle
int paddleWidth = 40;
int paddleHeight = 8;
int paddleX = 100;
int paddleY = 120;
int paddleSpeed = 5;

void loop() {
  StickCP2.update();

  // Move paddle
  if (StickCP2.BtnA.isPressed()) {
    paddleX = paddleX + paddleSpeed; // can shorten to paddleX += paddleSpeed
    if (paddleX + paddleWidth > screenWidth) { // Right boundary check
      paddleX = screenWidth - paddleWidth;
    } 
  }
  if (StickCP2.BtnB.isPressed()) {
    paddleX = paddleX - paddleSpeed; // can shorten to paddleX -= paddleSpeed
    if (paddleX < 0) { // Left boundary check
      paddleX = 0;
    }
  }

  // Update ball
  if (!gameOver) {
    handleBall();
  } else {
    delay(700);
    resetGame();
  }

  // Draw everything
  sprite->fillScreen(BLACK);
  sprite->fillRect(paddleX, paddleY, paddleWidth, paddleHeight, ORANGE);
  if (ball.active) {
    sprite->fillCircle(ball.x, ball.y, ball.size, GREEN);
  }

  // Score display
  sprite->setTextColor(WHITE);
  sprite->setTextSize(1);
  sprite->drawString("Score: " + String(score), 5, 5);

  sprite->pushSprite(0, 0);
}

// HELPER FUNCTIONS:
void resetBall() {
  ball.x = screenWidth / 2;
  ball.y = screenHeight / 2;
  ball.size = 5;
  ball.speedX = (random(0, 2) == 0) ? 2 : -2;
  ball.speedY = -2;
  ball.active = true;
}

void resetGame() {
  paddleX = screenWidth / 2 - paddleWidth / 2;
  paddleY = screenHeight - 15;

  resetBall();
  score = 0;
  gameOver = false;
}

void handleBall() {
  if (!ball.active) return;

  ball.x += ball.speedX;
  ball.y += ball.speedY;

  // Bounce off walls
  if (ball.x <= 0 || ball.x + ball.size >= screenWidth) {
    ball.speedX *= -1;
  }

  // Bounce off top
  if (ball.y <= 0) {
    ball.speedY *= -1;
  }

  // Paddle collision
  if (ball.y + ball.size >= paddleY && ball.y + ball.size <= paddleY + paddleHeight &&
      ball.x + ball.size >= paddleX && ball.x <= paddleX + paddleWidth) {
    ball.speedY *= -1;
    ball.y = paddleY - ball.size;

    StickCP2.Speaker.tone(1200, 30);
    score++;

    // Speed up slightly every 5 points
    if (score % 5 == 0) {
      if (ball.speedX > 0) ball.speedX++;
      else ball.speedX--;
      if (ball.speedY > 0) ball.speedY++;
      else ball.speedY--;
    }
  }

  // Missed ball
  if (ball.y + ball.size >= screenHeight) {
    ball.active = false;
    gameOver = true;
  }
}


