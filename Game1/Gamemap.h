#ifndef Gamemap_H_
#define Gamemap_H_
#define Max_Tile 20 // dạng map
#include "BaseObject.h"
#include "commonFunction.h"
class Tile  : public LTexture {
    public:
			Tile() {;}
			~Tile() {;}
};

class GameMap 
{
public:
	GameMap() ;
	~GameMap() ;

	void LoadText( const char*  name);// load từ file lấy dữ liệu cho map
	void LoadTiles() ;  // load hình ảnh map
	void DrawMap() ;
	Map GetMap() const { return game_map_ ; };
	void SetMap(Map & map_data_ ) {game_map_ = map_data_ ;};
private:
	Map game_map_ ;
	Tile tile_map_[Max_Tile]; // mảng chứa dữ liệu hình ảnh map
};
#endif