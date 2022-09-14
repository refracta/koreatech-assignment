public abstract class AbstractSoldierAdapter extends Soldier {
    @Override
    public abstract int attack();

    @Override
    public abstract void defend(int hitPower);

    @Override
    public abstract void heal();

    @Override
    public abstract boolean isLive();

    @Override
    public abstract int getHealth();
}
