//----------------------------------------
// Ascll Project Game Map Library
//----------------------------------------
#ifndef ASCLL_PROJECT_GAME_MAP_LIBRARY_MAP_VIEW
#define ASCLL_PROJECT_GAME_MAP_LIBRARY_MAP_VIEW


namespace game {

	class MapView {
	private:
		//�E�B���h�E�n���W
		int32_t wxs{};//�n�_X
		int32_t wys{};//�n�_Y
		int32_t wxc{};//���_X
		int32_t wyc{};//���_Y
		int32_t wxe{};//�I�_X
		int32_t wye{};//�I�_Y
		//�E�B���h�E�n����
		int32_t ww{};//�g�̉��̒���[px]
		int32_t wh{};//�g�̏c�̒���[px]
	public:
		//get
		int32_t getWindowStartX()const { return wxs; }
		int32_t getWindowStartY()const { return wys; }
		int32_t getWindowCenterX()const { return wxc; }
		int32_t getWindowCenterY()const { return wyc; }
		int32_t getWindowEndX()const { return wxe; }
		int32_t getWindowEndY()const { return wye; }
		int32_t getWindowWidth()const { return ww; }
		int32_t getWindowHeight()const { return wh; }

	private:

		constexpr void setWindowStartX(const int32_t wxs_) {
			wxs = wxs_;
			wxc = (wxe - wxs_) / 2;
			ww = wxe - wxs_;
		}
		constexpr void setWindowStartY(const int32_t wys_) {
			wys = wys_;
			wyc = (wye - wys_) / 2;
			wh = wye - wys_;
		}
		constexpr void setWindowCenterX(const int32_t wxc_) {
			wxc = wxc_;
		}
		constexpr void setWindowCenterY(const int32_t wyc_) {
			wyc = wyc_;
		}

		//�g���}�b�v����
		double th{};//�g���̏c�̒���
		double tw{};//�g���̉��̒���
		//�}�b�v(�`�b�v)�n���W
		double mxs{};//�n�_X
		double mys{};//�n�_Y
		double mxc{};//���_X
		double myc{};//���_Y
		double mxe{};//�I�_X
		double mye{};//�I�_Y
		int32_t mxcs{};//0��[�`�b�v�̎n�_X
		int32_t mycs{};//0��[�`�b�v�̎n�_Y
		int32_t mxce{};//0��[�`�b�v�̏I�_X
		int32_t myce{};//0��[�`�b�v�̏I�_Y
		//�}�b�v(�`�b�v)�n����
		size_t mw{};//0�S�̂̉��̒���
		size_t mh{};//0�S�̂̏c�̒���
				//�}�b�v�s�N�Z����
		double pw{};//�`�b�v�̉��̒���[px]
		double ph{};//�`�b�v�̏c�̒���[px]
	public:
		//get
		constexpr double getMapArrayWindowWidth()const { return tw; }
		constexpr double getMapArrayWindowHeight()const { return th; }
		constexpr double getMapArrayStartX()const { return mxs; }
		constexpr double getMapArrayStartY()const { return mys; }
		constexpr double getMapArrayCenterX()const { return mxc; }
		constexpr double getMapArrayCenterY()const { return myc; }
		constexpr double getMapArrayEndX()const { return mxe; }
		constexpr double getMapArrayEndY()const { return mye; }
		constexpr int32_t getMapArrayCeilStartX()const { return mxcs; }
		constexpr int32_t getMapArrayCeilStartY()const { return mycs; }
		constexpr int32_t getMapArrayCeilEndX()const { return mxce; }
		constexpr int32_t getMapArrayCeilEndY()const { return myce; }
		constexpr size_t getMapArrayWidth()const { return mw; }
		constexpr size_t getMapArrayHeight()const { return mh; }
		constexpr double getMapArrayPixelWidth()const { return pw; }
		constexpr double getMapArrayPixelHeight()const { return ph; }
		//set
		constexpr void setMapArrayWidth(const size_t x_) { mw = x_; }
		constexpr void setMapArrayHeight(const size_t y_) { mh = y_; }
		constexpr void setMapArraySize(const size_t x_, const size_t y_) {
			setMapArrayWidth(x_);
			setMapArrayHeight(y_);
		}
		template<typename vector_>
		constexpr void setMapArraySize(const vector_& vec_) {
			setMapArrayWidth(((mh = vec_.size()) == 0) ? 0 : vec_.front().size());
		}
		constexpr void setMapArray(const size_t xy_) {
			setMapArraySize(xy_, xy_);
		}
		void setMapArrayCeil() {
			mxcs = (int32_t)std::ceil(mxs);
			mycs = (int32_t)std::ceil(mys);
			mxce = (int32_t)std::ceil(mxe);
			myce = (int32_t)std::ceil(mye);
		}
		void changeMapArrayWindow() {
			mxs = mxc - tw / 2;
			mys = myc - th / 2;
			mxe = mxc + tw / 2;
			mye = myc + th / 2;
			pw = ww / tw;
			ph = wh / th;
			setMapArrayCeil();
		}
		void setMapArrayWindowWidth(const double tw_) {
			tw = tw_;
			th = wh * tw_ / ww;
			changeMapArrayWindow();
		}
		void setMapArrayWindowHeight(const double th_) {
			th = th_;
			tw = ww * th_ / wh;
			changeMapArrayWindow();
		}
		void setMapArrayWindow(const double tw_,const double th_) {
			tw = tw_;
			th = th_;
			changeMapArrayWindow();
		}

	public:
		MapView() = default;
		//�r���[������(�g�n�_X, �g�n�_Y, �g�I�_X, �g�I�_Y, �}�b�v���S���WX, �}�b�v���S���WY, ��ʕ\���}�X��Y)
		constexpr MapView(const int32_t wxs_, const int32_t wys_, const int32_t wxe_, const int32_t wye_, const double mxc_, const double myc_, const double th_)
			:wxs(wxs_),
			wys(wys_),
			wxc((wxe_ - wxs_) / 2),
			wyc((wye_ - wys_) / 2),
			wxe(wxe_),
			wye(wye_),
			ww(wxe_ - wxs_),
			wh(wye_ - wys_),
			th(th_),
			tw(ww*th_ / wh),
			mxs(mxc_ - tw / 2),
			mys(myc_ - th_ / 2),
			mxe(mxc_ + tw / 2),
			mye(myc_ + th_ / 2),
			mxc(mxc_),
			myc(myc_),
			pw(ww / tw),
			ph(wh / th) {}
		//�r���[������(�g�I�_X, �g�I�_Y, �}�b�v���S���WX, �}�b�v���S���WY, ��ʕ\���}�X��Y)
		constexpr MapView(const int32_t wxe_, const int32_t wye_, const double mxc_, const double myc_, const double th_)
			:wxs(0),
			wys(0),
			wxc(wxe_ / 2),
			wyc(wye_ / 2),
			wxe(wxe_),
			wye(wye_),
			ww(wxe_),
			wh(wye_),
			th(th_),
			tw(ww*th_ / wh),
			mxs(mxc_ - tw / 2),
			mys(myc_ - th_ / 2),
			mxe(mxc_ + tw / 2),
			mye(myc_ + th_ / 2),
			mxc(mxc_),
			myc(myc_),
			pw(ww / tw),
			ph(wh / th) {}
		//�r���[������(�g�n�_X, �g�n�_Y, �g�I�_X, �g�I�_Y, �}�b�v���S���WX, �}�b�v���S���WY, ��ʕ\���}�X��Y)
		void reset(const int32_t wxs_, const int32_t wys_, const int32_t wxe_, const int32_t wye_, const double mxc_, const double myc_, const double th_) {
			wxs = wxs_;
			wys = wys_;
			wxc = (wxe_ - wxs_) / 2;
			wyc = (wye_ - wys_) / 2;
			wxe = wxe_;
			wye = wye_;
			ww = wxe_ - wxs_;
			wh = wye_ - wys_;
			th = th_;
			tw = ww * th_ / wh;
			mxs = mxc_ - tw / 2;
			mys = myc_ - th_ / 2;
			mxe = mxc_ + tw / 2;
			mye = myc_ + th_ / 2;
			mxc = mxc_;
			myc = myc_;
			pw = ww / tw;
			ph = wh / th;
			setMapArrayCeil();
		}
		//�r���[������(�g�I�_X, �g�I�_Y, �}�b�v���S���WX, �}�b�v���S���WY, ��ʕ\���}�X��Y)
		void reset(const int32_t wxe_, const int32_t wye_, const double mxc_, const double myc_, const double th_) {
			wxs = 0;
			wys = 0;
			wxc = wxe_ / 2;
			wyc = wye_ / 2;
			wxe = wxe_;
			wye = wye_;
			ww = wxe_;
			wh = wye_;
			th = th_;
			tw = ww * th_ / wh;
			mxs = mxc_ - tw / 2;
			mys = myc_ - th_ / 2;
			mxe = mxc_ + tw / 2;
			mye = myc_ + th_ / 2;
			mxc = mxc_;
			myc = myc_;
			pw = ww / tw;
			ph = wh / th;
			setMapArrayCeil();
		}
		void setMapView(const double mxc_, const double myc_) {
			mxc = mxc_;
			myc = myc_;
			mxs = mxc_ - tw / 2;
			mys = myc_ - th / 2;
			mxe = mxc_ + tw / 2;
			mye = myc_ + th / 2;
			setMapArrayCeil();
		}
		void setMapView(const double mxyc_) {
			setMapView(mxyc_, mxyc_);
		}
		void setMapViewHalf(const double mxc_, const double myc_) {
			setMapView(mxc_ + 0.5, myc_ + 0.5);
		}
		void setMapViewHalf(const double mxyc_) {
			setMapView(mxyc_ + 0.5);
		}

		//��肪��������true
		constexpr bool checkTile() const {
			return (mw == 0 || mh == 0 || mxcs == mxce || mycs == myce);
		}

		constexpr int32_t setWindowCeilStartX()const {
			return (int32_t)(wxc - (mxc - mxcs + 1)*pw);
		}
		constexpr int32_t setWindowCeilStartY()const {
			return (int32_t)(wyc - (myc - mycs + 1)*ph);
		}
		//�}�b�v�̏o��(Y���W , X���W , �n�_X , �n�_Y , �I�_X , �I�_Y , (�C�ӂ̕ϐ�))
		template<class... Args>
		constexpr void outputMap(void(*f)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, const Args&...), const Args&... args) const {
			if (checkTile()) return;

			const int32_t wxcs{ setWindowCeilStartX() };
			const int32_t wycs{ setWindowCeilStartY() };
			const int32_t pw0{ (int32_t)pw };
			const int32_t ph0{ (int32_t)ph };

			for (int32_t i{ mycs }, wycs_i{ wycs }; i <= myce; ++i) {
				wycs_i += ph0;
				if (i < 0 || i >= mh) continue;
				for (int32_t j{ mxcs }, wxcs_j{ wxcs }; j <= mxce; ++j) {
					wxcs_j += pw0;
					if (j < 0 || j >= mw) continue;
					(*f)(i, j, wxcs_j, wycs_i, pw0, ph0, args...);
				}
			}
		}
		//�}�b�v�̏o��(Y���W , X���W , �n�_X , �n�_Y , �I�_X , �I�_Y , (�C�ӂ̕ϐ�))
		template<class... Args>
		constexpr void outputMapOver(void(*f)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, const Args&...), const Args&... args) const {
			if (checkTile()) return;

			const int32_t wxcs{ setWindowCeilStartX() };
			const int32_t wycs{ setWindowCeilStartY() };
			const int32_t pw0{ (int32_t)pw };
			const int32_t ph0{ (int32_t)ph };

			for (int32_t i{ mycs }, wycs_i{ wycs }; i <= myce; ++i) {
				wycs_i += ph0;
				for (int32_t j{ mxcs }, wxcs_j{ wxcs }; j <= mxce; ++j) {
					wxcs_j += pw0;
					(*f)(i, j, wxcs_j, wycs_i, pw0, ph0, args...);
				}
			}
		}
		//�}�b�v�̃��[�v�o��(Y���W , X���W , �n�_X , �n�_Y , �I�_X , �I�_Y , (�C�ӂ̕ϐ�))
		template<class... Args>
		constexpr void outputMapLoop(void(*f)(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, const Args&...), const Args&... args) const {
			if (checkTile()) return;

			const int32_t wxcs{ setWindowCeilStartX() };
			const int32_t wycs{ setWindowCeilStartY() };
			const int32_t pw0{ (int32_t)pw };
			const int32_t ph0{ (int32_t)ph };
			int32_t mxcs0{ mxcs };
			int32_t mycs0{ mycs };
			int32_t mxce0{ mxce };
			int32_t myce0{ myce };
			while (mycs0 < 0) {
				mycs0 += (int32_t)mh;
				myce0 += (int32_t)mh;
			}
			while (mxcs0 < 0) {
				mxcs0 += (int32_t)mw;
				mxce0 += (int32_t)mw;
			}

			for (int32_t i{ mycs0 }, wycs_i{ wycs }; i <= myce0; ++i) {
				wycs_i += ph0;
				for (int32_t j{ mxcs0 }, wxcs_j{ wxcs }; j <= mxce0; ++j) {
					wxcs_j += pw0;
					(*f)(i% (int32_t)mh, j% (int32_t)mw, wxcs_j, wycs_i, pw0, ph0, args...);
				}
			}
		}
		constexpr void limitMapArrayCenter() {
			if (mh == 0 || mw == 0) return;
			while (mxc < 0) mxc += (double)mw;
			while (myc < 0) myc += (double)mh;
			if (mxc >= (double)mw) mxc = std::fmod(mxc, (double)mw);
			if (myc >= (double)mh) myc = std::fmod(myc, (double)mh);
		}
		constexpr void limitMapArrayCenter(double& mxc_, double& myc_) {
			if (mh == 0 || mw == 0) return;
			while (mxc_ < 0) mxc_ += (double)mw;
			while (myc_ < 0) myc_ += (double)mh;
			if (mxc_ >= (double)mw) mxc_ = std::fmod(mxc_, (double)mw);
			if (myc_ >= (double)mh) myc_ = std::fmod(myc_, (double)mh);
		}


	};

}

#endif // ASCLL_PROJECT_GAME_MAP_LIBRARY_MAP_VIEW