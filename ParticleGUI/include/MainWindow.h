#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "NGLScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void keyPressEvent(QKeyEvent *_event) override;
	void setNumParticles(int _numParticles);
	private:
		Ui::MainWindow *ui;
		NGLScene *m_gl;


};
#endif // MAINWINDOW_H
