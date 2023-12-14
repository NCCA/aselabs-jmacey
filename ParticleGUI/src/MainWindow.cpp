#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_gl = new NGLScene(ui->numParticles->value(),  this);
	ui->mainWindowGridLayout->addWidget(m_gl,0,0,2,2);
	connect(ui->resetParticles,SIGNAL(clicked()),m_gl,SLOT(clearParticles()) );

	connect(ui->addParticles,&QPushButton::clicked,
	[=]()
	{
						m_gl->addParticles(ui->particlesToAdd->value());
	});

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
	switch(_event->key())
	{
	case Qt::Key_R : m_gl->clearParticles(); break;
	case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
	}
}

void MainWindow::setNumParticles(int _numParticles)
{
	ui->numParticles->setValue(_numParticles);
	m_gl->setNumParticles(_numParticles);
}


