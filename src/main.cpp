#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Strategy Design Pattern

using namespace std;
class AudioStrategy
{
public:
    virtual void play(const string &filename) const = 0;
};

class MP3AudioStrategy : public AudioStrategy
{
public:
    void play(const string &filename) const override
    {
        cout << "Playing MP3 file: " << filename << std::endl;
    }
};

class WAVAudioStrategy : public AudioStrategy
{
public:
    void play(const string &filename) const override
    {
        cout << "Playing WAV file: " << filename << std::endl;
    }
};

// Adapter Design Pattern
class AudioAdapter
{
private:
    AudioStrategy *audioStrategy;

public:
    AudioAdapter(AudioStrategy *strategy) : audioStrategy(strategy) {}

    void playAudio(const string &filename) const
    {
        audioStrategy->play(filename);
    }
};

// Context using Strategy and Adapter
class AudioManager
{
private:
    std::vector<string> audioFiles;
    std::unique_ptr<AudioAdapter> audioAdapter;

public:
    AudioManager(unique_ptr<AudioAdapter> adapter) : audioAdapter(move(adapter)) {}

    void addAudioFile(const string &filename)
    {
        audioFiles.push_back(filename);
    }

    void playAll() const
    {
        for (const auto &file : audioFiles)
        {
            audioAdapter->playAudio(file);
        }
    }
};

int main()
{
    // Strategy
    AudioStrategy *mp3Strategy = new MP3AudioStrategy();
    AudioStrategy *wavStrategy = new WAVAudioStrategy();

    // Adapter
    std::unique_ptr<AudioAdapter> mp3Adapter(new AudioAdapter(mp3Strategy));
    std::unique_ptr<AudioAdapter> wavAdapter(new AudioAdapter(wavStrategy));

    // Context
    std::unique_ptr<AudioManager> audioManager(new AudioManager(std::move(mp3Adapter)));

    // Allowing user input
    cout << "Enter audio file names (enter 'q' to stop):" << std::endl;
    string filename;
    while (true)
    {
        cout << "Enter file name: ";
        cin >> filename;

        if (filename == "q")
        {
            break;
        }

        audioManager->addAudioFile(filename);
    }

    // Choosing strategy
    cout << "Choose audio format (1 for MP3, 2 for WAV): ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        audioManager->playAll(); // MP3 strategy
    }
    else if (choice == 2)
    {
        audioManager.reset(new AudioManager(std::move(wavAdapter)));
        audioManager->playAll(); // WAV strategy
    }
    else
    {
        cout << "Invalid choice. Exiting." << std::endl;
    }

    // Clean up
    delete mp3Strategy;
    delete wavStrategy;

    return 0;
}
