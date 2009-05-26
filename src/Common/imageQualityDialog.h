/**
 * This file is a part of Qtpfsgui package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2006,2007,2008 Giuseppe Rota
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Giuseppe Rota <grota@users.sourceforge.net>
 */

#ifndef IMAGEQUALITYDIALOG_IMPL_H
#define IMAGEQUALITYDIALOG_IMPL_H

#include <QDialog>
#include "../generated_uic/ui_imageQualityDialog.h"

class ImageQualityDialog : public QDialog, private Ui::ImgQualityDialog
{
Q_OBJECT

public:
	ImageQualityDialog(QImage *img, QString fmt, QWidget *parent = 0);
	~ImageQualityDialog();
	int getQuality(void);
protected slots:
	void calcFileSize(void);
	void reset(int);
protected:
	const QImage *image;
	QString format;
};
#endif
