#include "skeletondemogui.h"

SkeletonDemoGUI::SkeletonDemoGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	// отступ элементов
	ui.centralWidget->setContentsMargins(6, 6, 6, 6);

	// сопоставление раскладок
	ui.centralWidget->setLayout(ui.horizontalLayout);

	connect(ui.openImageButton, SIGNAL(clicked()), this, SLOT(openImageButtonClicked()));

	connect(this, SIGNAL(newImageLoaded(QString)), ui.Painter, SLOT(imageChanged(QString)));

	connect(ui.circlesCB, SIGNAL(stateChanged(int)), this, SLOT(checkBoxesChanged(int)));
	connect(ui.bonesCB, SIGNAL(stateChanged(int)), this, SLOT(checkBoxesChanged(int)));
	connect(ui.contoursCB, SIGNAL(stateChanged(int)), this, SLOT(checkBoxesChanged(int)));
	connect(ui.imageCB, SIGNAL(stateChanged(int)), this, SLOT(checkBoxesChanged(int)));
	
	connect(ui.refreshSkeletonButton, SIGNAL(clicked()), this, SLOT(updateSkeleton()));

	connect(ui.saveImageButton, SIGNAL(clicked()), this, SLOT(saveImage()));

    connect(ui.savePolyButton, SIGNAL(clicked()), this, SLOT(savePolygons()));

	skeleton = NULL;
	srcimg = NULL;
}

SkeletonDemoGUI::~SkeletonDemoGUI()
{

}

void SkeletonDemoGUI::openImageButtonClicked()
{
	QFileDialog* fileDialog = new QFileDialog(this);
	
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	fileDialog->setNameFilter("Изображения (*.png *.jpg *.bmp)");

	QStringList fileNames;

	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}

	if (fileNames.size() != 0) {
		
		imagepath = fileNames.at(0);
		string filepath = string(fileNames.at(0).toLocal8Bit().constData());
		string filename = "Имя файла: ";
		int index = 0;
		
        for (ulong i = 0; i < filepath.size(); i++) {
			if (filepath[i] == '/') {
				index = i + 1;
			}
		}

        for (ulong i = index; i < filepath.size(); i++) {
			filename.push_back(filepath[i]);
		}

		ui.filenameLabel->setText(filename.c_str());

        updateSkeleton();
	}
}

void SkeletonDemoGUI::checkBoxesChanged(int)
{
	bool flag = false;
	if (ui.Painter->ready == true) {
		ui.Painter->ready = false;
		flag = true;
	}
	ui.Painter->drawBones = (ui.bonesCB->checkState() == Qt::Checked);
	ui.Painter->drawCircles = (ui.circlesCB->checkState() == Qt::Checked);
	ui.Painter->drawContours = (ui.contoursCB->checkState() == Qt::Checked);
	ui.Painter->drawImage = (ui.imageCB->checkState() == Qt::Checked);
	if (flag) {
		ui.Painter->ready = true;
	}
	ui.Painter->update();
}

void SkeletonDemoGUI::updateSkeleton()
{
	if (imagepath.size() != 0) {
		// скелетизация
        image = QImage(imagepath);

        if (skeleton != NULL) {
            delete skeleton;
        }

        clock_t tic = clock();

		if (srcimg) {
			delete srcimg;
		}

		srcimg = new BitRaster(image.width(), image.height());

        bool inverted = ui.invertCheckBox->checkState() == Qt::Checked;

		for (int i = 0; i < image.height(); i++) {
			for(int j = 0; j < image.width(); j++) {
				bool isBlack = qGreen(image.pixel(j, i)) < 128;
                if (!inverted) {
                    if (isBlack) {
                        srcimg->setBit(j, i, isBlack);
                    }
                }
                else {
                    if (!isBlack) {
                        srcimg->setBit(j, i, !isBlack);
                    }
                }
			}
		}

		BondSkeletTrans(srcimg, ui.pruning->value(), ui.area->value(), skeleton);
		
		clock_t toc = clock();

		// время выполнения
		char buffer[500];
		sprintf(buffer,
			"TimeTrace: %d мс\n"
			"TimeTree: %d мс\n"
			"TimeSkelet: %d мс\n"
			"TimePrun: %d мс\n"
			"Total: %d мс\n"
			"Total wrap: %d мс\n"
			"Connected comp.: %d \n"
			"Polygons: %d \n",
			skeleton->RTab.TimeTrace,
			skeleton->RTab.TimeTree,
			skeleton->RTab.TimeSkelet,
			skeleton->RTab.TimePrun,
			skeleton->RTab.Total,
			int(1000 * double(toc - tic) / CLOCKS_PER_SEC),
			skeleton->RTab.ConnectComp,
			skeleton->RTab.Polygons
			);
		ui.timeLabel->setText(buffer);

		ui.Painter->ready = false;

		ui.Painter->skeleton = skeleton;
		
		emit(newImageLoaded(imagepath));

		ui.Painter->ready = true;
		ui.Painter->update();
	}
}

void SkeletonDemoGUI::saveImage()
{
	QPixmap qpimage = QPixmap::grabWidget(ui.Painter, 0, 0, image.width(), image.height());

	QFileDialog* fileDialog = new QFileDialog(this);
	
	fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setNameFilter("Изображение (*.png)");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);

	QStringList fileNames;

	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}

	if (fileNames.size() != 0) {
        QString filen = fileNames.at(0);

        if (!filen.endsWith(".png")) {
            filen += ".png";
        }

		qpimage.save(filen);
	}
}

void SkeletonDemoGUI::savePolygons()
{
    if (skeleton != NULL) {
        QFileDialog* fileDialog = new QFileDialog(this);

        fileDialog->setFileMode(QFileDialog::AnyFile);
        fileDialog->setNameFilter("Полигоны (*.txt)");
        fileDialog->setAcceptMode(QFileDialog::AcceptSave);

        QStringList fileNames;

        if (fileDialog->exec()) {
            fileNames = fileDialog->selectedFiles();
        }

        if (fileNames.size() != 0) {
            QString filen = fileNames.at(0);

            if (!filen.endsWith(".txt")) {
                filen += ".txt";
            }

            // print polygons in file
            vector<string> edgesList;

            TContour* S = skeleton->Boundary->first();
            while (S != NULL) {
                int cornersCount = S->ListPoints->cardinal();
                TPoint** points = new TPoint*[cornersCount];
                int i = 0;
                TPoint* Corn = S->ListPoints->first();
                while (Corn != NULL)
                {
                    points[i++] = Corn;
                    Corn = Corn->getNext();
                }
                for (int j = 0; j < cornersCount - 1; j++) {
                    stringstream ss;
                    ss << points[j]->X << " " << points[j]->Y << " " << points[j + 1]->X << " " << points[j + 1]->Y;
                    edgesList.push_back(ss.str());
                }
                stringstream ss;
                ss << points[cornersCount - 1]->X << " " << points[cornersCount - 1]->Y << " " << points[0]->X << " " << points[0]->Y;
                edgesList.push_back(ss.str());

                delete points;
                S = S->getNext();
            }

            ofstream f(filen.toStdString().c_str());
            f << "0" << endl;
            f << edgesList.size() << endl;
            for (ulong i = 0; i < edgesList.size(); ++i) {
                f << edgesList[i] << endl;
            }
            f.close();
        }
    }
}
