#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

struct Position {
  float x, y, z;
};

struct Velocity {
  float dx, dy, dz;
};

struct alignas(64) EcsChunk {
  // In this example used 2 entities. However tht total entities is of 585
  // complete 16 KB(chunk- line cache)
  static const int MAX_ENTITIES = 2;

  uint32_t entitites[MAX_ENTITIES];

  Velocity velocity[MAX_ENTITIES];

  Position position[MAX_ENTITIES];
};

struct alignas(64) Buffer {

  EcsChunk chunk1;
  EcsChunk chunk2;
};

class HandleBuffer {
private:
  Buffer buffer1;
  Buffer buffer2;
  Buffer buffer3;

public:
  Buffer *ptr_escritura = &buffer1;
  Buffer *ptr_lectura = &buffer2;
  Buffer *ptr_intermediate = &buffer3;

  uint8_t activeThreads = 0;
  uint8_t maxNumberThreads = 0;

  bool completeFrame = false;

  std::mutex mutex;
  std::condition_variable conditionVariable;

  void InitHandleBuffer(uint8_t totalThreads) {

    std::lock_guard<std::mutex> lock(mutex);
    activeThreads = totalThreads;
    maxNumberThreads = totalThreads;
  }

  void ThreadFinishWork() {

    bool allReady = false;
    {
      std::lock_guard<std::mutex> lock(mutex);
      activeThreads--;

      if (activeThreads == 0) {
        allReady = true;

        std::swap(ptr_escritura, ptr_intermediate);

        activeThreads = maxNumberThreads;
        completeFrame = true;
      }
    }

    if (allReady) {
      conditionVariable.notify_one();
    }
  }

  void SwapAndRenderFrame() {

    // SWAP BUFFERS
    std::unique_lock<std::mutex> lock(mutex);

    conditionVariable.wait(lock, [this]() { return completeFrame; });

    std::swap(ptr_intermediate, ptr_lectura);

    completeFrame = false;

    lock.unlock();

    // RENDER FRAME
    for (const auto *_chunk : {&ptr_lectura->chunk1, &ptr_lectura->chunk2}) {
      for (int i = 0; i < 2; i++) {
        std::cout << "Entitie: " << _chunk->entitites[i] << "\n"
                  << "Velocity: " << _chunk->velocity[i].dx << ", "
                  << _chunk->velocity[i].dy << ", " << _chunk->velocity[i].dz
                  << std::endl
                  << "Position: " << _chunk->position[i].x << ", "
                  << _chunk->position[i].y << ", " << _chunk->position[i].z
                  << std::endl;

        std::cout << "[FINISH FRAME]\n";
      }
    }
  }
};

HandleBuffer handle;

// SISTEMS
void VelocitySystem(EcsChunk &chunk) {

  std::this_thread::sleep_for(std::chrono::milliseconds(15));

  for (int i = 0; i < 2; i++) {
    chunk.velocity[i].dx += 1.5f;
    chunk.velocity[i].dy += 1.5f;
    chunk.velocity[i].dz += 1.5f;
  }
}

void PositionSystem(EcsChunk &chunk) {

  std::this_thread::sleep_for(std::chrono::milliseconds(15));

  for (int i = 0; i < 2; i++) {
    chunk.position[i].x += 0.5f;
    chunk.position[i].y += 0.5f;
    chunk.position[i].z += 0.5f;
  }
}

void ThreadSystem(EcsChunk &_chunk) {

  VelocitySystem(_chunk);
  PositionSystem(_chunk);
  handle.ThreadFinishWork();
}

int main() {

  std::cout << "[ENGINE INITIALIZED]\n";

  for (int i = 0; i < 2; i++) {
    handle.ptr_escritura->chunk1.entitites[i] = i;
    handle.ptr_escritura->chunk2.entitites[i] = i + 10;
  }

  *handle.ptr_lectura = *handle.ptr_escritura;
  *handle.ptr_intermediate = *handle.ptr_escritura;

  handle.InitHandleBuffer(2);

  for (int i = 0; i < 2; i++) {

    std::thread hilo_1(ThreadSystem, std::ref(handle.ptr_escritura->chunk1));
    std::thread hilo_2(ThreadSystem, std::ref(handle.ptr_escritura->chunk2));

    handle.SwapAndRenderFrame();

    hilo_1.join();
    hilo_2.join();
  }

  std::cout << "[ENGINE FINISHED]\n";

  return 0;
}
