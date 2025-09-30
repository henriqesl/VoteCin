// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Cria uma instância do player
    player = new QMediaPlayer(this);

    // 2. Conecta o player à "tela" (o QVideoWidget que você adicionou na interface)
    player->setVideoOutput(ui->videoWidget); // 'videoWidget' é o nome do seu QVideoWidget

    // 3. Define a fonte do vídeo como uma URL da internet!
    //    (Este é um link de exemplo para um vídeo .mp4)
    QUrl videoUrl("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4");
    player->setSource(videoUrl);

    // 4. Adiciona um botão para tocar o vídeo
    // Conecta o clique do botão 'playButton' ao slot 'play' do player
    connect(ui->playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui->pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
}

MainWindow::~MainWindow()
{
    delete ui;
}
