

#include "RecordPanel.h"

RecordPanel::RecordPanel(QWidget *parent)
	:QWidget(parent) {

	ui.setupUi(this);

	
	

	// ��ȭ��
	ui.timeLabel->hide();
	ui.resumeButton->hide();
	ui.pauseButton->hide();
	ui.stopButton->hide();
	

	/*// ��ȭ��
	ui.recordButton->hide();
	ui.quitButton->hide();
	ui.resumeButton->hide();
	*/


	/* //�Ͻ�����
	ui.recordButton->hide();
	ui.quitButton->hide();
	ui.pauseButton->hide();
	*/
	

	
}

RecordPanel::~RecordPanel() {

}
